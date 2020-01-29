#include <stdio.h>         // NULL
#include <stdlib.h>        // strtol()
#include <stdbool.h>       // bool
#include <string.h>        // memcpy()
#include "flash.h"
#include "static_queue.h"
#include "S32R274.h"       // C55FMC
#include "console_api.h"   // PRINTF()
#include "console_cmd.h"   // console_command_reg()
#include "console.h"       // put_string()
#include "sbc_fs8x.h"      // fs8x_wd_handle()
#include "SWT.h"           // clear_SWT0_counter()
#include "Utility.h"       // Delay_us()
#if FLASH_DEBUG
#include "SPT.h"
#endif

#define MUTEX_LOCK(x)       (x) = 1
#define MUTEX_UNLOCK(x)     (x) = 0
#define MUTEX_IS_LOCKED(x)  (x)

enum _FlashPrivateConst {
  kFlashQueueCap =  8,  // queue capacity for tasks
  kFlashBlockCap = 21,  // block capacity for private memory table
};

typedef enum _FlashRegion {
  kUTest          = 0x00,  // table
  kEeprom         = 0x01,
  kCse2           = 0x02,
  kMiddle         = 0x03,
  kLarge          = 0x04,
  kFlashRegionCap = 0x05,
} flash_rgn_t;

typedef enum _QueueHandle {
  kIsEmpty        = 0x01,
  kIsFull         = 0x02,
  kEnqueue        = 0x03,
  kProcess        = 0x04,  // dequeue task or perform task I/O.
} que_hdl_t;

typedef enum _IoMode {
  kNonBlocking    = 0x01,
  kBlocking       = 0x02,
} io_mode_t;

typedef struct _FlashArg {
  uint32_t base;
  uint32_t limit;
  void *   src;
} flash_arg_t;

typedef flash_st (*flash_routine)(flash_arg_t *);

typedef struct _FlashTask {
  flash_routine func;
  flash_arg_t   arg;
  void *        (*callback)(void *);
  void *        callback_arg;
} flash_task_t ;

typedef struct _FlashQueue {
  QUEUE_MEMBERS(flash_task_t);
} FlashQueue;

typedef struct _FlashPrivate {
  uint32_t base;
  uint32_t size;
  uint32_t unlock;
  uint32_t sel;     // selection
} flash_priv_t;

typedef struct _FlashPrivateRegion {
  uint32_t base;
  uint32_t limit;
  uint32_t lock;
  uint32_t desel;   // de-selection
} flash_priv_rgn_t;

typedef struct _FlashIX {
  flash_task_t task;
  uint32_t     rgn_base;
  uint32_t     rgn_limit;
} flash_ix_t;

/************************************************
 * Forward Declarations                         *
 ************************************************/
void flash_init(void);
void flash_isr(void);
bool is_flash_io_done(void);
// Non-Blocking I/O (NIO) API
flash_st flash_erase(uint32_t addr, uint32_t size,
                     void *(*callback)(void *), void *arg);
flash_st flash_write(uint32_t addr, void *src, uint32_t size,
                     void *(*callback)(void *), void *arg);
flash_st flash_write64(uint32_t addr, uint64_t data);
// Blocking I/O (BIO) API
flash_st flash_erase_BIO(uint32_t addr, uint32_t size);
flash_st flash_write_BIO(uint32_t addr, void *src, uint32_t size);
flash_st flash_write64_BIO(uint32_t addr, uint64_t data);
// UTest API
flash_st utest_write_BIO(uint32_t addr, void *src, uint32_t size);
flash_st utest_write64_BIO(uint32_t addr, uint64_t data);
// EEPROM API
flash_st eeprom_erase_BIO(uint32_t addr, uint32_t size);
flash_st eeprom_write_BIO(uint32_t addr, void *src, uint32_t size);
flash_st eeprom_write64_BIO(uint32_t addr, uint64_t data);
//
bool flash_blkcmp(uint32_t addr1, uint32_t addr2);
bool flash_rgncmp(uint32_t addr1, uint32_t addr2);
flash_st flash_next_blk(const void **ptr);
#if FLASH_DEBUG
flash_st flash_dump(uint32_t, uint32_t);
#endif

// Private Methods
static void init_flash_state(void);
static inline void transit_state(flash_st);
static flash_st ix_checker(io_mode_t, flash_ix_t *);
static flash_st state_machine_nio(flash_st (*)(flash_ix_t *), flash_ix_t *);
static flash_st state_machine_bio(flash_st (*)(flash_ix_t *), flash_ix_t *);
static inline flash_st perform_nio(flash_ix_t *);
static flash_st perform_bio(flash_ix_t *);
static int8_t que_handler(que_hdl_t, flash_task_t *, uint32_t);
static bool arg_handler(flash_arg_t *, uint32_t);
static inline void enable_isr(void);
static inline void disable_isr(void);
static flash_st check_erase_arg(flash_arg_t *, uint32_t, uint32_t);
static flash_st check_write_arg(flash_arg_t *, uint32_t, uint32_t);
static flash_priv_t *flash_priv_get(uint32_t);
static flash_priv_rgn_t *flash_priv_rgn_get(uint32_t);
static flash_st flash_sub_erase(flash_arg_t *);
static flash_st flash_sub_write(flash_arg_t *);
static flash_st post_flash_erase(flash_arg_t *);
static flash_st post_flash_write(flash_arg_t *);
static void flash_tester(char **, int);
static void utest_tester(char **, int);
static void eeprom_tester(char **, int);
#if FLASH_DEBUG
static void test_console(char **, int);
static void callback_dummy(void);
#endif

/************************************************
 * Globals                                      *
 ************************************************/
blk16k_t __attribute__((section(".eeprom"))) kEepromPars[kEepromBlockCap];
blk64k_t __attribute__((section(".blackbox"))) kBlackBox[kBlackboxBlockCap];
static flash_task_t kTask[kFlashQueueCap];  // memory of task queue
static FlashQueue kQueue;                   // instance of task queue
static flash_st kState = kFlashReady;  // state machine
static uint8_t kBioMutex = 0;          // 0: unlock; 1: lock; default: 0
static const flash_priv_t kPriv[kFlashBlockCap] = {
  //     base,       size,     unlock,     select
  {0x00400000,    0x04000, 0x3FFFFFFF, 0x80000000},  //  16 KiB utest-block0
                                                     //  << reserved >>
  {0x00800000,    0x04000, 0xBFFEFFFF, 0x00010000},  //  16 KiB eeprom-block0
  {0x00804000,    0x04000, 0xBFFBFFFF, 0x00040000},  //  16 KiB eeprom-block1
  {0x00808000,    0x04000, 0xBFFDFFFF, 0x00020000},  //  16 KiB eeprom-block2
  {0x0080C000,    0x04000, 0xBFF7FFFF, 0x00080000},  //  16 KiB eeprom-block3
                                                     //  << reserved >>
  {0x00A00000,    0x04000, 0xFFFFFFFE, 0x00000001},  //  16 KiB cse2-block0
  {0x00A04000,    0x04000, 0xFFFFFFFD, 0x00000002},  //  16 KiB cse2-block1
                                                     //  << reserved >>
  {0x00F98000,    0x04000, 0xBFFFFFFE, 0x00000001},  //  16 KiB block0
  {0x00F9C000,    0x04000, 0xBFFFFFFD, 0x00000002},  //  16 KiB block1
  {0x00FA0000,    0x10000, 0xBFFFFFFB, 0x00000004},  //  64 KiB block2
  {0x00FB0000,    0x10000, 0xBFFFFFF7, 0x00000008},  //  64 KiB block3
  {0x00FC0000,    0x10000, 0xBFFFFFEF, 0x00000010},  //  64 KiB block4
  {0x00FD0000,    0x10000, 0xBFFFFFDF, 0x00000020},  //  64 KiB block5
  {0x00FE0000,    0x10000, 0xBFFFFFBF, 0x00000040},  //  64 KiB block6
  {0x00FF0000,    0x10000, 0xBFFFFF7F, 0x00000080},  //  64 KiB block7

  {0x01000000,    0x40000, 0xFFFFFFFE, 0x00000001},  // 256 KiB block8
  {0x01040000,    0x40000, 0xFFFFFFFD, 0x00000002},  // 256 KiB block9
  {0x01080000,    0x40000, 0xFFFFFFFB, 0x00000004},  // 256 KiB block10
  {0x010C0000,    0x40000, 0xFFFFFFF7, 0x00000008},  // 256 KiB block11
  {0x01100000,    0x40000, 0xFFFFFFEF, 0x00000010},  // 256 KiB block12
  {0x01140000,    0x40000, 0xFFFFFFDF, 0x00000020},  // 256 KiB block13
};
static const flash_priv_rgn_t kPrivRgn[kFlashRegionCap] = {
  //     base,      limit,       lock,  de-select
  {0x00400000, 0x00404000, 0xBFFFFFFF, 0x00000000},  // utest
  {0x00800000, 0x00810000, 0xBFFFFFFF, 0x00000000},  // eeprom
  {0x00A00000, 0x00F98000, 0x0000FFFF, 0x00000000},  // cse2
  {0x00F98000, 0x01000000, 0xBFFFFFFF, 0x00000000},  // middle
  {0x01000000, 0x01180000, 0xFFFFFFFF, 0x00000000},  // large
};

/************************************************
 * APIs                                         *
 ************************************************/
void flash_init(void)
{
  // Init task queue of flash I/O.
  InitQueue(&kQueue, kFlashQueueCap, kTask, sizeof(flash_task_t));
  // Init flash state.
  init_flash_state();
  // Set priority for flash I/O interrupt.
  INTC.PSR[185].R = 0x8001;
  // Original command registration.
  console_command_reg("flash_tester", flash_tester);
  console_command_reg("utest_tester", utest_tester);
  console_command_reg("eeprom_tester", eeprom_tester);
#if FLASH_DEBUG
  console_command_reg("flash", test_console);
#endif
}

void flash_isr(void)
{
  flash_arg_t *task_arg = &kQueue.items[kQueue.head].arg;

  // Reset C55FMC's register after I/O done.
  if (1 == C55FMC.MCR.B.PGM)
    post_flash_write(task_arg);
  else if (1 == C55FMC.MCR.B.ERS)
    post_flash_erase(task_arg);

  que_handler(kProcess, NULL, 0);

  // Off ISR register if BIO requested and current task completed.
  //   or task queue is empty.
  if ((MUTEX_IS_LOCKED(kBioMutex) && task_arg->limit == task_arg->base)
      || que_handler(kIsEmpty, NULL, 0)) {
    disable_isr();
    transit_state(kFlashReady);
  }
}

bool is_flash_io_done(void)
{
  return C55FMC.MCR.B.DONE != 0;
}

flash_st flash_erase(uint32_t addr, uint32_t size,
                     void *(*callback)(void *), void *callback_arg)
{
  flash_ix_t ix = {
    {flash_sub_erase, {addr, addr+size, NULL}, callback, callback_arg},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st err = ix_checker(kNonBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_nio(perform_nio, &ix);
}

flash_st flash_write(uint32_t addr, void *src, uint32_t size,
                     void *(*callback)(void *), void *callback_arg)
{
  flash_ix_t ix = {
    {flash_sub_write, {addr, addr+size, src}, callback, callback_arg},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st err = ix_checker(kNonBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_nio(perform_nio, &ix);
}

flash_st flash_write64(uint32_t addr, uint64_t data)
{
  return flash_write(addr, &data, sizeof(data), NULL, NULL);
}

flash_st flash_erase_BIO(uint32_t addr, uint32_t size)
{
  flash_ix_t ix = {
    {flash_sub_erase, {addr, addr+size, NULL}, NULL, NULL},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st err = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_bio(perform_bio, &ix);
}

flash_st flash_write_BIO(uint32_t addr, void *src, uint32_t size)
{
  flash_ix_t ix = {
    {flash_sub_write, {addr, addr+size, src}, NULL, NULL},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st err = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_bio(perform_bio, &ix);
}

flash_st flash_write64_BIO(uint32_t addr, uint64_t data)
{
  return flash_write_BIO(addr, &data, sizeof(data));
}

flash_st utest_write_BIO(uint32_t addr, void *src, uint32_t size)
{
  flash_ix_t ix = {
    {flash_sub_write, {addr, addr+size, src}, NULL, NULL},
    kPrivRgn[kUTest].base, kPrivRgn[kUTest].limit
  };
  flash_st err = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_bio(perform_bio, &ix);
}

flash_st utest_write64_BIO(uint32_t addr, uint64_t data)
{
  return utest_write_BIO(addr, &data, sizeof(data));
}

flash_st eeprom_erase_BIO(uint32_t addr, uint32_t size)
{
  flash_ix_t ix = {
    {flash_sub_erase, {addr, addr+size, NULL}, NULL, NULL},
    kPrivRgn[kEeprom].base, kPrivRgn[kEeprom].limit
  };
  flash_st err = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_bio(perform_bio, &ix);
}

flash_st eeprom_write_BIO(uint32_t addr, void *src, uint32_t size)
{
  flash_ix_t ix = {
    {flash_sub_write, {addr, addr+size, src}, NULL, NULL},
    kPrivRgn[kEeprom].base, kPrivRgn[kEeprom].limit
  };
  flash_st err = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != err)
    return err;

  return state_machine_bio(perform_bio, &ix);
}

flash_st eeprom_write64_BIO(uint32_t addr, uint64_t data)
{
  return eeprom_write_BIO(addr, &data, sizeof(data));
}

bool flash_blkcmp(uint32_t addr1, uint32_t addr2)
{
  flash_priv_t *priv1 = flash_priv_get(addr1);
  flash_priv_t *priv2 = flash_priv_get(addr2);

  if (NULL != priv1 && NULL != priv2 && priv1 == priv2)
    return true;
  else
    return false;
}

bool flash_rgncmp(uint32_t addr1, uint32_t addr2)
{
  flash_priv_rgn_t *prgn1 = flash_priv_rgn_get(addr1);
  flash_priv_rgn_t *prgn2 = flash_priv_rgn_get(addr2);

  if (NULL != prgn1 && NULL != prgn2 && prgn1 == prgn2)
    return true;
  else
    return false;
}

flash_st flash_next_blk(const void **ptr)
{
  flash_priv_t *priv = flash_priv_get((uint32_t)*ptr);

  if (NULL == priv)
    return kFlashInvalidAddr;
  else {
    *ptr = (const void *)(priv + 1)->base;
    return kFlashSuccess;
  }
}

#if FLASH_DEBUG
flash_st flash_dump(uint32_t start, uint32_t end)
{
  flash_priv_rgn_t *prgn_s = flash_priv_rgn_get(start);
  flash_priv_rgn_t *prgn_e = flash_priv_rgn_get(end);

  if (NULL == prgn_s || NULL == prgn_e)
    return kFlashInvalidAddr;

  uint32_t *p;

  for (uint32_t thru = start; thru < end; thru += kSinglePage) {
    if (0 == thru % (32 * kSinglePage))  // 1 KiB
      PRINTF("  --Flash: dump address 0x%lX--\n", (uint32_t)thru);
    p = (uint32_t *)thru;
#ifdef ENABLE_SWT
    clear_SWT0_counter();
#endif
    fs8x_wd_handle(fs8xFlash);
    PRINTF("  %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n",
           p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    Delay_us(3000);
  }
  return kFlashSuccess;
}
#endif

/************************************************
 * Private Methods                              *
 ************************************************/

static void init_flash_state(void)
{
  MUTEX_UNLOCK(kBioMutex);

  if (0 == C55FMC.MCR.B.PECIE && 1 == C55FMC.MCR.B.DONE)
    kState = kFlashReady;
  else if (1 == C55FMC.MCR.B.PECIE && 1 == C55FMC.MCR.B.DONE)
    kState = kFlashIsrReady;
  else if (0 == C55FMC.MCR.B.PECIE && 0 == C55FMC.MCR.B.DONE)
    kState = kFlashBioBusy;
  else if (1 == C55FMC.MCR.B.PECIE && 0 == C55FMC.MCR.B.DONE)
    kState = kFlashNioBusy;
}

static inline void transit_state(flash_st new_state)
{
  kState = new_state;
}

static flash_st ix_checker(io_mode_t io_rout, flash_ix_t *ix)
{
  switch (io_rout) {
    case kNonBlocking:
      if (que_handler(kIsFull, NULL, 0)) {
        PRINTF("  flash: queue is full!\n");
        return kFlashQueueOverrun;
      }
      break;
    case kBlocking:
      break;
    default:
      break;
  }

  flash_st err;

  if (flash_sub_erase == ix->task.func)
    err = check_erase_arg(&ix->task.arg, ix->rgn_base, ix->rgn_limit);
  else if (flash_sub_write == ix->task.func)
    err = check_write_arg(&ix->task.arg, ix->rgn_base, ix->rgn_limit);
  if (kFlashSuccess != err)
    return err;

  return kFlashSuccess;
}

static flash_st state_machine_nio(flash_st (*func_nio)(flash_ix_t *),
                                  flash_ix_t *ix)
{
  switch (kState) {
    case kFlashReady:
      func_nio(ix);  // enqueue
      enable_isr();
      transit_state(kFlashNioBusy);
      que_handler(kProcess, NULL, 0);
      break;
    case kFlashIsrReady:
    case kFlashNioBusy:
      func_nio(ix);  // enqueue
      break;
    case kFlashBioBusy:
      return kFlashIoBusy;  // interrupt to invoke NIO is not allowed
      break;
    default:
      return kFlashAbnormal;
      break;
  }
  return kFlashSuccess;
}

static flash_st state_machine_bio(flash_st (*func_bio)(flash_ix_t *),
                                  flash_ix_t *ix)
{
  switch (kState) {
    case kFlashReady:
      transit_state(kFlashBioBusy);
      func_bio(ix);
      transit_state(kFlashReady);
      // Reset ISR register and continue NIO if task queue is not empty.
      if (!que_handler(kIsEmpty, NULL, 0)) {
        enable_isr();
        transit_state(kFlashNioBusy);
        que_handler(kProcess, NULL, 0);
      }
      break;
    case kFlashIsrReady:
      disable_isr();
      transit_state(kFlashReady);
      state_machine_bio(func_bio, ix);
      break;
    case kFlashBioBusy:
      return kFlashIoBusy;
      break;
    case kFlashNioBusy:
      MUTEX_LOCK(kBioMutex);    // lock mutex of BIO
      while (kFlashReady != kState)
        ;                       // waiting for NIO current task completed
      state_machine_bio(func_bio, ix);
      MUTEX_UNLOCK(kBioMutex);  // unlock mutex of BIO
      break;
    default:
      return kFlashAbnormal;
      break;
  }
  return kFlashSuccess;
}

static inline flash_st perform_nio(flash_ix_t *ix)
{
  que_handler(kEnqueue, &ix->task, 0);

  return kFlashSuccess;
}

static flash_st perform_bio(flash_ix_t *ix)
{
  if (0 == C55FMC.MCR.B.DONE) {  // error handling for blocking I/O
    PRINTF("  flash: I/O busy!\n");
    return kFlashIoBusy;
  }

  flash_arg_t *arg = &ix->task.arg;
  flash_routine func = ix->task.func;

  while (arg->base < arg->limit && kFlashSuccess == func(arg)) {
    while (0 == C55FMC.MCR.B.DONE) {
#ifdef ENABLE_SWT
      clear_SWT0_counter();
#endif
      fs8x_wd_handle(fs8xFlash);
    }
    if (flash_sub_erase == func)
      post_flash_erase(arg);
    else if (flash_sub_write == func)
      post_flash_write(arg);
  }
  return kFlashSuccess;
}

static int8_t que_handler(que_hdl_t operation, flash_task_t *enq_task,
                          uint32_t step_size)
{
  flash_routine func = kQueue.items[kQueue.head].func;
  flash_arg_t *task_arg = &kQueue.items[kQueue.head].arg;
  void *(*callback)(void *) = kQueue.items[kQueue.head].callback;
  void *callback_arg = kQueue.items[kQueue.head].callback_arg;

  switch (operation) {
    case kIsEmpty:
      return kQueue.IsEmpty(&kQueue);
    case kIsFull:
      return kQueue.IsFull(&kQueue);
    case kEnqueue:
      return kQueue.Enqueue(&kQueue, enq_task);
    case kProcess:
      if (task_arg->limit == task_arg->base) {  // if task completed
        kQueue.Dequeue(&kQueue, NULL);
        if (NULL != callback)
          callback(callback_arg);
      } else                                    // otherwise, execute flash I/O
        func(task_arg);
      break;
    default:
      return kFlashAbnormal;
      break;
  }
  return kQueueSuccess;
}

static bool arg_handler(flash_arg_t *arg, uint32_t step_size)
{
  static uint32_t pgm_size = 0;

  // Update pgm_size, always return false. Invoked in flash_pub_erase/write.
  if (0 != step_size && 0 == pgm_size) {
    pgm_size = step_size;
    return false;
  }
  // Update arg, check completed. Invoked after post_flash_erase/write.
  else if (NULL != arg && 0 != pgm_size) {
    if (NULL != arg->src)
      arg->src += pgm_size;
    arg->base += pgm_size;
    pgm_size = 0;
    return arg->limit == arg->base;
  }
  // Check if arg completed.
  else if (NULL != arg && 0 == step_size && 0 == pgm_size) {
    return arg->limit == arg->base;
  }
  // Not supposed to be, re-initialize pgm_size.
  else {
    pgm_size = 0;
    return false;
  }
}

static inline void enable_isr(void)
{
  C55FMC.MCR.B.PECIE = 1;  // Enable Interrupt
}

static inline void disable_isr(void)
{
  C55FMC.MCR.B.PECIE = 0;  // Disable Interrupt
}

static flash_st check_erase_arg(flash_arg_t *arg,
                                uint32_t low_bound, uint32_t up_bound)
{
  const flash_priv_t *priv;
  uint32_t base = arg->base;
  uint32_t size = arg->limit - arg->base;
  uint32_t limit = arg->limit;

  if (NULL == (priv = flash_priv_get(base))  // find private table
      || low_bound > base                    // lower bound
      || up_bound <= base + size) {          // upper bound
    PRINTF("  flash: invalid address %lX!\n", base);
    return kFlashInvalidAddr;
  }

  // Update arg new base and limit
  arg->base = priv->base;
  for (; (arg->limit = priv->base+priv->size) < limit; ++priv)
    ;
  return kFlashSuccess;
}

static flash_st check_write_arg(flash_arg_t *arg,
                                uint32_t low_bound, uint32_t up_bound)
{
  uint32_t base = arg->base;
  uint32_t size = arg->limit - arg->base;
  void *src = arg->src;

  if (NULL == flash_priv_get(base)   // find private table
      || low_bound > base            // lower bound
      || up_bound <= base + size     // upper bound
      || 0 != base % kDoubleWord) {
    PRINTF("  flash: invalid address %lX!\n", base);
    return kFlashInvalidAddr;
  }
  if (NULL == src) {
    PRINTF("  flash: NULL pointer!\n");
    return kFlashNullPointer;
  }
  if (0 != size % kDoubleWord) {
    PRINTF("  flash: invalid size aligned %lX!\n", size);
    return kFlashInvalidSize;
  }
  return kFlashSuccess;
}

static flash_priv_t *flash_priv_get(uint32_t addr)
{
  const flash_priv_t *limit = &kPriv[kFlashBlockCap];

  for (const flash_priv_t *priv = kPriv; priv < limit; ++priv)
    if (addr >= priv->base && addr < (priv->base + priv->size))
      return (flash_priv_t *)priv;
  return NULL;
}

static flash_priv_rgn_t *flash_priv_rgn_get(uint32_t addr)
{
  const flash_priv_rgn_t *limit = &kPrivRgn[kFlashRegionCap];

  for (const flash_priv_rgn_t *prgn = kPrivRgn; prgn < limit; ++prgn)
    if (addr >= prgn->base && addr < prgn->limit)
      return (flash_priv_rgn_t *)prgn;
  return NULL;
}

static flash_st flash_sub_erase(flash_arg_t *task_arg)
{
  flash_priv_t *priv = flash_priv_get(task_arg->base);

  if (NULL == priv)
    return kFlashInvalidAddr;

  if (priv->base >= kPrivRgn[kLarge].base) {
    C55FMC.LOCK2.R = priv->unlock;  // Unlock block
    C55FMC.SEL2.R = priv->sel;      // Select block for erasing
  }
  else if (priv->base >= kPrivRgn[kMiddle].base) {
    C55FMC.LOCK0.R = priv->unlock;
    C55FMC.SEL0.R = priv->sel;
  }
  else if (priv->base >= kPrivRgn[kCse2].base) {
    C55FMC.LOCK1.R = priv->unlock;
    C55FMC.SEL1.R = priv->sel;
  }
  else if (priv->base >= kPrivRgn[kEeprom].base) {
    C55FMC.LOCK0.R = priv->unlock;
    C55FMC.SEL0.R = priv->sel;
  }
  // No condition of erasing UTest region.

  C55FMC.MCR.B.PEAS = 0;            // Activate main array space
  C55FMC.MCR.B.ERS = 1;             // Enable Erase
  // Perform Interlock write (necessary)
  *(uint64_t *)priv->base = 0xFFFFFFFFFFFFFFFF;

  // Update program size of task argument in function static variable.
  arg_handler(NULL, priv->base + priv->size - task_arg->base);

  C55FMC.MCR.B.EHV = 1;             // Start internal erase sequence
  return kFlashSuccess;
}

static flash_st flash_sub_write(flash_arg_t *task_arg)
{
  flash_priv_t *priv = flash_priv_get(task_arg->base);
  // Data must be aligned to 64-bit
  uint64_t *dest = (uint64_t *)task_arg->base;
  uint64_t *src = (uint64_t *)task_arg->src;
  // Segment limit is absolute address 128-Byte aligned
  // i.e. cross-segment flash write is not allowed. PEG error.
  uint32_t seg_limit = (task_arg->base + kQuadPage) / kQuadPage * kQuadPage;
  uint32_t pgm_size;

  if (NULL == priv)
    return kFlashInvalidAddr;

  if (priv->base >= kPrivRgn[kLarge].base) {
    C55FMC.LOCK2.R = priv->unlock;  // Unlock block
  }
  else if (priv->base >= kPrivRgn[kMiddle].base) {
    C55FMC.LOCK0.R = priv->unlock;
  }
  else if (priv->base >= kPrivRgn[kCse2].base) {
    C55FMC.LOCK1.R = priv->unlock;
  }
  else if (priv->base >= kPrivRgn[kEeprom].base) {
    C55FMC.LOCK0.R = priv->unlock;
  }
  else if (priv->base >= kPrivRgn[kUTest].base) {
    C55FMC.LOCK0.R = priv->unlock;
    C55FMC.MCR.B.PEAS = 1;          // Activate UTest NVM space
  }

  if (seg_limit < task_arg->limit)
    pgm_size = seg_limit - task_arg->base;
  else
    pgm_size = task_arg->limit - task_arg->base;
  if (pgm_size >= kQuadPage)
    pgm_size = kQuadPage;

  // Perform Interlock write (necessary)
  *(uint64_t *)priv->base = 0xFFFFFFFFFFFFFFFF;
  C55FMC.MCR.B.PGM = 1;             // Enable Programming

  for (uint16_t i = 0; i < pgm_size/kDoubleWord; ++i)
    *dest++ = *src++;               // Save data

  // Update program size of task argument in function static variable.
  arg_handler(NULL, pgm_size);

  C55FMC.MCR.B.EHV = 1;             // Start programming
  return kFlashSuccess;
}

static flash_st post_flash_erase(flash_arg_t *task_arg)
{
  flash_priv_rgn_t *prgn = flash_priv_rgn_get(task_arg->base);

  if (NULL == prgn)
    return kFlashInvalidAddr;

  C55FMC.MCR.B.EHV = 0;           // Disable high voltage
  C55FMC.MCR.B.ERS = 0;           // End erasing

  if (prgn->base >= kPrivRgn[kLarge].base) {
    C55FMC.LOCK2.R = prgn->lock;  // Lock block
    C55FMC.SEL2.R = prgn->desel;  // De-select block for erasing
  }
  else if (prgn->base >= kPrivRgn[kMiddle].base) {
    C55FMC.LOCK0.R = prgn->lock;
    C55FMC.SEL0.R = prgn->desel;
  }
  else if (prgn->base >= kPrivRgn[kCse2].base) {
    C55FMC.LOCK1.R = prgn->lock;
    C55FMC.SEL1.R = prgn->desel;
  }
  else if (prgn->base >= kPrivRgn[kEeprom].base) {
    C55FMC.LOCK0.R = prgn->lock;
    C55FMC.SEL0.R = prgn->desel;
  }
  // No condition of erasing UTest region.

  // Renew base address of task argument.
  arg_handler(task_arg, 0);

  if (0 == C55FMC.MCR.B.PEG || 1 == C55FMC.MCR.B.RWE) {
    C55FMC.MCR.B.RWE = 1;         // Reset read-while-write error
    PRINTF("  flash: erase failed %lX!\n", task_arg->base);
    return kFlashEraseError;
  }
  return kFlashSuccess;
}

static flash_st post_flash_write(flash_arg_t *task_arg)
{
  flash_priv_rgn_t *prgn = flash_priv_rgn_get(task_arg->base);

  if (NULL == prgn)
    return kFlashInvalidAddr;

  C55FMC.MCR.B.EHV = 0;           // Disable high voltage
  C55FMC.MCR.B.PGM = 0;           // End programming
  C55FMC.MCR.B.PEAS = 0;          // Activate main array space

  if (prgn->base >= kPrivRgn[kLarge].base)
    C55FMC.LOCK2.R = prgn->lock;  // Lock block
  else if (prgn->base >= kPrivRgn[kMiddle].base)
    C55FMC.LOCK0.R = prgn->lock;
  else if (prgn->base >= kPrivRgn[kCse2].base)
    C55FMC.LOCK1.R = prgn->lock;
  else if (prgn->base >= kPrivRgn[kEeprom].base)
    C55FMC.LOCK0.R = prgn->lock;
  else if (prgn->base >= kPrivRgn[kUTest].base)
    C55FMC.LOCK0.R = prgn->lock;

  // Renew base address of task argument.
  arg_handler(task_arg, 0);

  if (0 == C55FMC.MCR.B.PEG || 1 == C55FMC.MCR.B.RWE) {
    C55FMC.MCR.B.RWE = 1;         // Reset read-while-write error
    PRINTF("  flash: program failed %lX!\n", task_arg->base);
    return kFlashProgramError;
  }
  return kFlashSuccess;
}

// Tester
static void flash_tester(char **argv, int argc)
{
  uint32_t src = 0;
  uint32_t dest = 0;
  uint64_t data = 0;
  if (argc > 1)
    dest = strtoul(argv[1], NULL, 16) & 0xFFFFFFF8;  // addr 8-Byte aligned
  if (argc > 2)
    src = strtoul(argv[2], NULL, 16) & 0xFFFFFF80;   // addr 128-Byte aligned
  if (argc > 3)
    data = strtoull(argv[3], NULL, 16);

  if (dest > 0 && src == 0 && data == 0)
    flash_erase_BIO(dest, 0);
  else if (dest > 0 && src > 0 && data > 0)
    flash_write_BIO(dest, (void *)src, (uint32_t)data);
  else if (argc > 3 && dest > 0 && src == 0)
    flash_write64_BIO(dest, data);
}

static void utest_tester(char **argv, int argc)
{
  uint32_t *d;
  uint32_t dest;
  uint32_t src;
  uint32_t size = 0;
  uint16_t offs = 0;
  uint64_t data;

  if (argc < 2)
    return;

  offs = strtoul(argv[2], NULL, 16) & 0x3FF8;

  if (!strncmp("rd", argv[1], 2)) {
    d = (uint32_t *)(kPrivRgn[kUTest].base + offs);
    PRINTF("%08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n",
      (uint32_t)d, d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7]);
  }
  else if (!strncmp("wr", argv[1], 2) && argc > 4) {
    dest = kPrivRgn[kUTest].base + offs;
    src = strtoul(argv[3], NULL, 16) & 0xFFFFFFF0;
    size = strtoul(argv[4], NULL, 16) & 0x3FF0;
    if ((dest + size) > kPrivRgn[kUTest].limit) {
      PRINTF("utester: out of memory %08lX!\n", dest + size);
      return;
    }
    utest_write_BIO(dest, (void *)src, size);
  }
  else if (!strncmp("w64", argv[1], 3) && argc > 3) {
    data = strtoull(argv[3], NULL, 16);
    dest = kPrivRgn[kUTest].base + offs;
    utest_write64_BIO(dest, data);
  }
}

static void eeprom_tester(char **argv, int argc)
{
  uint32_t addr = strtoul(argv[2], NULL, 16);
  if(!strncmp(argv[1], "erase", 5)){
    eeprom_erase_BIO(addr, 0);
  }
  else if (!strncmp(argv[1], "write", 5) && argc >= 5){
    uint32_t src = strtoul(argv[3], NULL, 16);
    uint32_t count = strtoul(argv[4], NULL, 16);
    eeprom_write_BIO(addr, (void *)src, count);
  }
  else if (!strncmp(argv[1], "wr64", 4) && argc >= 4){
    uint64_t data = strtoll(argv[3], NULL, 16);
    eeprom_write64_BIO(addr, data);
  }
}

/**************************************************
 * Test                                           *
 **************************************************/
#if FLASH_DEBUG
static void test_console(char **argv, int argc)
{
  static uint8_t arr[80] = {0xFF};
  static uint8_t num = 0;
  uint8_t cnt;
  uint32_t base;
  uint32_t size;
  void *src;

  if (argc == 1) {
    PRINTF("----Flash: status----\n");
    PRINTF("flash dump <addr> <size>\n");
    PRINTF("flash erase <addr> <size>\n");
    PRINTF("flash write <addr> <size>\n");
  }
  else if (argc == 5 && !strcmp(argv[1], "test")) {
    base = strtoul(argv[2], NULL, 16);
    size = strtoul(argv[3], NULL, 16);
    cnt = strtoul(argv[4], NULL, 10);
    ++num;
    for (uint32_t i = 0; i < size; ++i)
      arr[i] = num;
    for (uint32_t i = 0; i < cnt; ++i) {
      flash_write(base, arr, size, (void *(*)(void *))callback_dummy, NULL);
      base += size;
    }
    flash_erase_BIO(base, size);
    flash_write_BIO(base, arr, size);
    PRINTF("  flash debug: test done!\n");
  }
  else if (argc == 4 && !strcmp(argv[1], "dump")) {
    base = strtoul(argv[2], NULL, 16);
    size = strtoul(argv[3], NULL, 16);
    flash_dump(base, base + size);
    PRINTF("  flash debug: dump done!\n");
  }
  else if (argc == 3 && !strcmp(argv[1], "erase") && !strcmp(argv[2], "eeprom")) {
    eeprom_erase_BIO(kPriv[1].base, 0);
    eeprom_erase_BIO(kPriv[2].base, 0);
    eeprom_erase_BIO(kPriv[3].base, 0);
    eeprom_erase_BIO(kPriv[4].base, 0);
    PRINTF("  flash debug: erase eeprom done!\n");
  }
  else if (argc == 4 &&
           (!strcmp(argv[1], "erase") || !strcmp(argv[1], "erase_bio"))) {
    base = strtoul(argv[2], NULL, 16);
    size = strtoul(argv[3], NULL, 16);
    if (!strcmp(argv[1], "erase"))
      flash_erase(base, size, (void *(*)(void *))callback_dummy, NULL);
    else
      flash_erase_BIO(base, size);
    PRINTF("  flash debug: erase done!\n");
  }
  else if ((argc == 4 || argc == 5) &&
           (!strcmp(argv[1], "write") || !strcmp(argv[1], "write_bio"))) {
    base = strtoul(argv[2], NULL, 16);
    size = strtoul(argv[3], NULL, 16);
    if (argc == 5)
      cnt = strtoul(argv[4], NULL, 10);
    else
      cnt = 1;
    ++num;
    for (uint32_t i = 0; i < size; ++i)
      arr[i] = num;
    for (uint8_t i = 0; i < cnt; ++i) {
      if (!strcmp(argv[1], "write"))
        flash_write(base, arr, size, (void *(*)(void *))callback_dummy, NULL);
      else
        flash_write_BIO(base, arr, size);
      base += size;
    }
    PRINTF("  flash debug: write done!\n");
  }
  else if (argc == 3 && (!strcmp(argv[1], "write64k"))) {
    base = strtoul(argv[2], NULL, 16);
    size = 0x10000;
    src = spt_work_space_get();
    PRINTF("spt work space addr: %p\n", src);
    flash_write(base, src, size, (void *(*)(void *))callback_dummy, NULL);
    PRINTF("  flash debug: write64k test done!\n");
  }
  else {
    PRINTF("----Flash: console error----\n");
  }
}

static void callback_dummy(void)
{
  static uint8_t i = 0;
  PRINTF("  flash debug: callback dummy - Hello World!  %u\n", ++i);
}
#endif
