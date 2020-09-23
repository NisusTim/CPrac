#include <stdio.h>          // NULL
#include <stdlib.h>         // strtol()
#include <stdbool.h>        // bool
#include <string.h>         // memcpy()
#include "flash.h"
#include "static_queue.h"
#include "S32R274.h"        // C55FMC
#include "console_api.h"    // PRINTF()
#include "console_cmd.h"    // console_command_reg()
#include "console.h"        // put_string()
#include "sbc_fs8x.h"       // fs8x_wd_handle()
#include "SWT.h"            // clear_SWT0_counter()
#include "Utility.h"        // Delay_ms()
#include "event.h"          // put_event()
#if FLASH_DEBUG
#include "SPT.h"            // spt_work_space_get()
#include "SWT.h"            // reset_system()
#endif

#define STR(x)              #x
#define FLSH_ID             STR(flsh)
#define MUTEX_LOCK(x)       (x) = 1
#define MUTEX_UNLOCK(x)     (x) = 0
#define MUTEX_IS_LOCKED(x)  (x)

enum _FlashPrivateConst {
  kFlashQueueCap  = 16,    // queue capacity for tasks
  kFlashBlockCap  = 21     // block capacity for private memory table
};

typedef enum _FlashRegion {
  kUTest          = 0x00,  // table
  kEeprom         = 0x01,
  kCse2           = 0x02,
  kMiddle         = 0x03,
  kLarge          = 0x04,
  kFlashRegionCap = 0x05
} flash_rgn_t;

typedef enum _QueueHandle {
  kIsInit         = 0x01,
  kIsEmpty        = 0x02,
  kIsFull         = 0x03,
  kEnqueue        = 0x04,
  kGetCurrentArg  = 0x05,
  kProcess        = 0x06   // dequeue task or perform task I/O.
} que_hdl_t;

typedef struct _FlashArg {
  uint32_t base;
  uint32_t limit;
  void *   src;
} flash_arg_t;

typedef flash_st (*flash_routine)(flash_arg_t *);

typedef struct _FlashTask {
  flash_routine func;
  flash_arg_t   arg;
  void          (*callback)(void *);
  void *        callback_arg;
} flash_task_t ;

typedef struct _FlashInterface {
  flash_task_t task;
  uint32_t     rgn_base;
  uint32_t     rgn_limit;
} flash_ix_t;

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

/************************************************
 * Forward Declarations                         *
 ************************************************/
void flash_init(void);
void flash_isr(void);
// Flash API
bool is_flash_on_safety(void);
flash_st flash_get_state(void);
flash_st flash_set_safety(bool safety_toggle);
flash_st flash_erase(uint32_t addr, uint32_t size,
                     void (*callback)(void *), void *arg);
flash_st flash_write(uint32_t addr, void *src, uint32_t size,
                     void (*callback)(void *), void *arg);
flash_st flash_write64(uint32_t addr, uint64_t data,
                       void (*callback)(void *), void *arg);
flash_st flash_erase_bio(uint32_t addr, uint32_t size);
flash_st flash_write_bio(uint32_t addr, void *src, uint32_t size);
flash_st flash_write64_bio(uint32_t addr, uint64_t data);
// UTEST API
flash_st utest_write_bio(uint32_t addr, void *src, uint32_t size);
flash_st utest_write64_bio(uint32_t addr, uint64_t data);
// EEPROM API
flash_st eeprom_erase(uint32_t addr, uint32_t size,
                      void (*callback)(void *), void *arg);
flash_st eeprom_write(uint32_t addr, void *src, uint32_t size,
                      void (*callback)(void *), void *arg);
flash_st eeprom_write64(uint32_t addr, uint64_t data,
                        void (*callback)(void *), void *arg);
flash_st eeprom_erase_bio(uint32_t addr, uint32_t size);
flash_st eeprom_write_bio(uint32_t addr, void *src, uint32_t size);
flash_st eeprom_write64_bio(uint32_t addr, uint64_t data);
//
bool is_flash_io_done(void);
bool flash_blkcmp(uint32_t addr1, uint32_t addr2);
bool flash_rgncmp(uint32_t addr1, uint32_t addr2);
flash_st flash_end_of_blk(const void **ptr);
flash_st flash_next_blk(const void **ptr);
bool is_flash_at_blk_base(uint32_t addr);
bool is_flash_rest_blk_blank(uint32_t addr);
flash_st flash_first_blank_segment(const void **ptr, uint32_t size, uint32_t step_size);
#if FLASH_DEBUG && FLASH_READ
flash_st flash_read(uint32_t, uint32_t);
#endif

// Private Methods
static void init_flash_state(void);
static inline void transit_state(flash_st);
static flash_st ix_checker(io_mode_t, flash_ix_t *);
static flash_st state_machine_nio(flash_task_t *);
static flash_st state_machine_bio(flash_task_t *);
static inline flash_st perform_nio(flash_task_t *);
static flash_st perform_bio(flash_task_t *);
static int8_t que_handler(que_hdl_t, flash_task_t *, flash_arg_t **);
static bool arg_handler(flash_arg_t *, uint32_t);
static inline void enable_isr(void);
static inline void disable_isr(void);
static flash_st check_erase_arg(flash_arg_t *, uint32_t, uint32_t);
static flash_st check_program_arg(flash_arg_t *, uint32_t, uint32_t);
static flash_priv_t *flash_priv_get(uint32_t);
static flash_priv_rgn_t *flash_priv_rgn_get(uint32_t);
static flash_st pre_flash_erase(flash_arg_t *);
static flash_st pre_flash_program(flash_arg_t *);
static flash_st post_flash_erase(flash_arg_t *);
static flash_st post_flash_program(flash_arg_t *);
static void flash_tester(char **, int);
static void utest_tester(char **, int);
static void eeprom_tester(char **, int);
#if FLASH_DEBUG
static const char *string_of_state(flash_st);
static void flash_print_register(void);
static void flash_help(void);
static void flash_dump(void);
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
  console_command_reg(FLSH_ID, test_console);
#endif
}

void flash_isr(void)
{
  flash_arg_t *task_arg;

  que_handler(kGetCurrentArg, NULL, &task_arg);

  // Reset C55FMC's register after I/O done.
  if (1 == C55FMC.MCR.B.PGM)
    post_flash_program(task_arg);
  else if (1 == C55FMC.MCR.B.ERS)
    post_flash_erase(task_arg);

  que_handler(kProcess, NULL, NULL);

  // Off ISR register if BIO requested and current task completed.
  //   or task queue is empty.
  if ((MUTEX_IS_LOCKED(kBioMutex) && task_arg->limit == task_arg->base)
      || que_handler(kIsEmpty, NULL, NULL)) {
    disable_isr();
    transit_state(kFlashReady);
  }
}

bool is_flash_on_safety(void)
{
  if (kFlashSafety == kState)
    return true;

  return false;
}

flash_st flash_get_state(void)
{
  return kState;
}

flash_st flash_set_safety(bool safety_toggle)
{
  static bool prev_toggle = false;
  static flash_st prev_state;

  if (true == safety_toggle && false == prev_toggle) {
    prev_toggle = true;
    prev_state = flash_get_state();
    transit_state(kFlashSafety);
    return kFlashSafety;
  } else if (false == safety_toggle && true == prev_toggle) {
    prev_toggle = false;
    transit_state(prev_state);
    return prev_state;
  }

  return kFlashAbnormal;
}

flash_st flash_erase(uint32_t addr, uint32_t size,
                     void (*callback)(void *), void *callback_arg)
{
  flash_ix_t ix = {
    {pre_flash_erase, {addr, addr+size, NULL}, callback, callback_arg},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st errno = ix_checker(kNonBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_nio(&ix.task);
}

flash_st flash_write(uint32_t addr, void *src, uint32_t size,
                     void (*callback)(void *), void *callback_arg)
{
  flash_ix_t ix = {
    {pre_flash_program, {addr, addr+size, src}, callback, callback_arg},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st errno = ix_checker(kNonBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_nio(&ix.task);
}

flash_st flash_write64(uint32_t addr, uint64_t data,
                       void (*callback)(void *), void *callback_arg)
{
  return flash_write(addr, &data, sizeof(data), callback, callback_arg);
}

flash_st flash_erase_bio(uint32_t addr, uint32_t size)
{
  flash_ix_t ix = {
    {pre_flash_erase, {addr, addr+size, NULL}, NULL, NULL},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st errno = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_bio(&ix.task);
}

flash_st flash_write_bio(uint32_t addr, void *src, uint32_t size)
{
  flash_ix_t ix = {
    {pre_flash_program, {addr, addr+size, src}, NULL, NULL},
    kPrivRgn[kCse2].base, kPrivRgn[kLarge].limit
  };
  flash_st errno = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_bio(&ix.task);
}

flash_st flash_write64_bio(uint32_t addr, uint64_t data)
{
  return flash_write_bio(addr, &data, sizeof(data));
}

flash_st utest_write_bio(uint32_t addr, void *src, uint32_t size)
{
  flash_ix_t ix = {
    {pre_flash_program, {addr, addr+size, src}, NULL, NULL},
    kPrivRgn[kUTest].base, kPrivRgn[kUTest].limit
  };
  flash_st errno = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_bio(&ix.task);
}

flash_st utest_write64_bio(uint32_t addr, uint64_t data)
{
  return utest_write_bio(addr, &data, sizeof(data));
}

flash_st eeprom_erase(uint32_t addr, uint32_t size,
                      void (*callback)(void *), void *callback_arg)
{
  flash_ix_t ix = {
    {pre_flash_erase, {addr, addr+size, NULL}, callback, callback_arg},
    kPrivRgn[kEeprom].base, kPrivRgn[kEeprom].limit
  };
  flash_st errno = ix_checker(kNonBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_nio(&ix.task);
}

flash_st eeprom_write(uint32_t addr, void *src, uint32_t size,
                      void (*callback)(void *), void *callback_arg)
{
  flash_ix_t ix = {
    {pre_flash_program, {addr, addr+size, src}, callback, callback_arg},
    kPrivRgn[kEeprom].base, kPrivRgn[kEeprom].limit
  };
  flash_st errno = ix_checker(kNonBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_nio(&ix.task);
}

flash_st eeprom_write64(uint32_t addr, uint64_t data,
                        void (*callback)(void *), void *callback_arg)
{
  return eeprom_write(addr, &data, sizeof(data), callback, callback_arg);
}

flash_st eeprom_erase_bio(uint32_t addr, uint32_t size)
{
  flash_ix_t ix = {
    {pre_flash_erase, {addr, addr+size, NULL}, NULL, NULL},
    kPrivRgn[kEeprom].base, kPrivRgn[kEeprom].limit
  };
  flash_st errno = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_bio(&ix.task);
}

flash_st eeprom_write_bio(uint32_t addr, void *src, uint32_t size)
{
  flash_ix_t ix = {
    {pre_flash_program, {addr, addr+size, src}, NULL, NULL},
    kPrivRgn[kEeprom].base, kPrivRgn[kEeprom].limit
  };
  flash_st errno = ix_checker(kBlocking, &ix);

  if (kFlashSuccess != errno)
    return errno;

  return state_machine_bio(&ix.task);
}

flash_st eeprom_write64_bio(uint32_t addr, uint64_t data)
{
  return eeprom_write_bio(addr, &data, sizeof(data));
}

bool is_flash_io_done(void)
{
  return C55FMC.MCR.B.DONE != 0;
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

flash_st flash_end_of_blk(const void **ptr)
{
  if (NULL == ptr)
    return kFlashNullPointer;

  flash_priv_t *priv = flash_priv_get((uint32_t)*ptr);

  // not in block table
  if (NULL == priv)
    return kFlashInvalidAddr;
  // end of block
  else {
    *ptr = (const void *)(priv->base + priv->size);
    return kFlashSuccess;
  }
}

flash_st flash_next_blk(const void **ptr)
{
  if (NULL == ptr)
    return kFlashNullPointer;

  flash_priv_t *priv = flash_priv_get((uint32_t)*ptr);
  const flash_priv_t *limit = &kPriv[kFlashBlockCap - 1];

  // not in block table or end of block table
  if (NULL == priv || limit == priv)
    return kFlashInvalidAddr;
  // next block
  else {
    *ptr = (const void *)(priv + 1)->base;
    return kFlashSuccess;
  }
}

bool is_flash_at_blk_base(uint32_t addr)
{
  flash_priv_t *priv = flash_priv_get(addr);

  if (NULL == priv || addr != priv->base)
    return false;

  return true;
}

bool is_flash_rest_blk_blank(uint32_t addr)
{
  flash_priv_t *priv = flash_priv_get(addr);
  const uint32_t base = (const uint32_t)(addr / kDoubleWord * kDoubleWord);
  const uint32_t limit = (const uint32_t)(priv->base + priv->size);

  // there's no case of (base == limit)
  if (NULL == priv)
    return false;  // kFlashInvalidAddr;

  for (uint32_t thru = (uint32_t)base; thru < limit; thru += kDoubleWord)
    if (kFlashBlank != *(uint64_t *)thru)
      return false;

  return true;
}

flash_st flash_first_blank_segment(const void **ptr, uint32_t size, uint32_t step_size)
{
  if (NULL == ptr)
    return kFlashNullPointer;
  if (kDoubleWord > size)
    size = kDoubleWord;
  if (0 != step_size % kDoubleWord)
    step_size = 0;

  flash_priv_t *priv = flash_priv_get((uint32_t)*ptr);
  const uint32_t base = (const uint32_t)
                         ((uint32_t)*ptr / kDoubleWord * kDoubleWord);
  const uint32_t limit = (const uint32_t)(priv->base + priv->size);
  const uint8_t cont_cnt = (const uint8_t)
                            ((size + kDoubleWord - 1) / kDoubleWord);
  uint32_t head = base;
  uint8_t cnt = 0;

  if (NULL == priv)
    return kFlashInvalidAddr;
  else if (limit < (uint32_t)*ptr + size)
    return kFlashInvalidSize;

  for (uint32_t thru = (uint32_t)base; thru < limit; thru += kDoubleWord) {
    if (kFlashBlank == *(uint64_t *)thru) {
      ++cnt;
      if (1 == cnt)
        head = thru;
      if (cont_cnt == cnt) {
        *ptr = (const void *)head;
        return kFlashSuccess;
      }
    } else {
      if (0 != step_size)
        thru = ((thru + step_size) / step_size) * step_size - kDoubleWord;
      cnt = 0;
    }
  }

  return kFlashAbnormal;  // no blank
}

#if FLASH_DEBUG && FLASH_READ
flash_st flash_read(uint32_t addr, uint32_t size)
{
  flash_priv_rgn_t *prgn_s = flash_priv_rgn_get(addr);
  flash_priv_rgn_t *prgn_e = flash_priv_rgn_get(addr + size);

  if (NULL == prgn_s || NULL == prgn_e)
    return kFlashInvalidAddr;

  uint32_t *p;

  for (uint32_t thru = addr; thru < addr + size; thru += kSinglePage) {
    if (0 == thru % (32 * kSinglePage))  // 1 KiB
      DBG_PRINTF("  --Flash: dump address 0x%08lX--\n", (uint32_t)thru);
    p = (uint32_t *)thru;
#ifdef ENABLE_SWT
    clear_SWT0_counter();
#endif
    fs8x_wd_handle(fs8xFlash);
    DBG_PRINTF("  %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX\n",
               p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    Delay_ms(3);
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

static flash_st ix_checker(io_mode_t io_mode, flash_ix_t *ix)
{
  switch (io_mode) {
    case kNonBlocking:
      if (que_handler(kIsFull, NULL, NULL)) {
        DBG_PRINTF("  flash: queue is full!\n");
        return kFlashQueueOverrun;
      }
      break;
    case kBlocking:
      break;
    default:
      break;
  }

  flash_st errno;

  if (pre_flash_erase == ix->task.func)
    errno = check_erase_arg(&ix->task.arg, ix->rgn_base, ix->rgn_limit);
  else if (pre_flash_program == ix->task.func)
    errno = check_program_arg(&ix->task.arg, ix->rgn_base, ix->rgn_limit);
  if (kFlashSuccess != errno)
    return errno;

  return kFlashSuccess;
}

static flash_st state_machine_nio(flash_task_t *task)
{
  switch (kState) {
    case kFlashReady:
      perform_nio(task);  // enqueue
      enable_isr();
      transit_state(kFlashNioBusy);
      que_handler(kProcess, NULL, NULL);
      break;
    case kFlashIsrReady:
    case kFlashNioBusy:
      perform_nio(task);  // enqueue
      break;
    case kFlashBioBusy:
      return kFlashIoBusy;  // interrupt to invoke NIO is not allowed
      break;
    case kFlashSafety:
      DBG_PRINTF("  flash: nio program/erase operation is forbidden on safety mode!\n");
      return kFlashSafety;  // low voltage protection
      break;
    default:
      return kFlashAbnormal;
      break;
  }
  return kFlashSuccess;
}

static flash_st state_machine_bio(flash_task_t *task)
{
  flash_st errno = kFlashSuccess;

  switch (kState) {
    case kFlashReady:
      transit_state(kFlashBioBusy);
      errno = perform_bio(task);
      transit_state(kFlashReady);
      // Reset ISR register and continue NIO if task queue is not empty.
      if (que_handler(kIsInit, NULL, NULL)
          && !que_handler(kIsEmpty, NULL, NULL)) {
        enable_isr();
        transit_state(kFlashNioBusy);
        que_handler(kProcess, NULL, NULL);
      }
      break;
    case kFlashIsrReady:
      disable_isr();
      transit_state(kFlashReady);
      errno = state_machine_bio(task);
      break;
    case kFlashBioBusy:
      return kFlashIoBusy;
      break;
    case kFlashNioBusy:
      MUTEX_LOCK(kBioMutex);    // lock mutex of BIO
      while (kFlashReady != kState) {  // waiting for NIO current task completed
#ifdef ENABLE_SWT
        clear_SWT0_counter();
#endif
        fs8x_wd_handle(fs8xFlash);
      }
      errno = state_machine_bio(task);
      MUTEX_UNLOCK(kBioMutex);  // unlock mutex of BIO
      break;
    case kFlashSafety:
      DBG_PRINTF("  flash: bio program/erase operation is forbidden on safety mode!\n");
      return kFlashSafety;  // low voltage protection
      break;
    default:
      return kFlashAbnormal;
      break;
  }
  return errno;
}

static inline flash_st perform_nio(flash_task_t *task)
{
  que_handler(kEnqueue, task, NULL);

  return kFlashSuccess;
}

static flash_st perform_bio(flash_task_t *task)
{
  if (0 == C55FMC.MCR.B.DONE) {  // error handling for blocking I/O
    DBG_PRINTF("  flash: I/O busy!\n");
    return kFlashIoBusy;
  }

  flash_st errno = kFlashSuccess;
  flash_arg_t *arg = &task->arg;
  flash_routine func = task->func;

  while (kFlashSuccess == errno && arg->base < arg->limit
         && kFlashSuccess == func(arg)) {
    while (0 == C55FMC.MCR.B.DONE) {
#ifdef ENABLE_SWT
      clear_SWT0_counter();
#endif
      fs8x_wd_handle(fs8xFlash);
    }
    if (pre_flash_erase == func)
      errno = post_flash_erase(arg);
    else if (pre_flash_program == func)
      errno = post_flash_program(arg);
  }
  return errno;
}

static int8_t que_handler(que_hdl_t operation, flash_task_t *enq_task,
                          flash_arg_t **curr_arg)
{
  flash_routine func = kQueue.items[kQueue.head].func;
  flash_arg_t *arg = &kQueue.items[kQueue.head].arg;
  void (*callback)(void *) = kQueue.items[kQueue.head].callback;
  void *callback_arg = kQueue.items[kQueue.head].callback_arg;

  switch (operation) {
    case kIsInit:
      if (0 != kQueue.capacity)
        return true;
      else {
        InitQueue(&kQueue, kFlashQueueCap, kTask, sizeof(flash_task_t));
        return false;
      }
    case kIsEmpty:
      return kQueue.IsEmpty(&kQueue);
    case kIsFull:
      return kQueue.IsFull(&kQueue);
    case kEnqueue:
      return kQueue.Enqueue(&kQueue, enq_task);
    case kGetCurrentArg:
      *curr_arg = &kQueue.items[kQueue.head].arg;
      break;
    case kProcess:
      if (arg->limit == arg->base) {  // if task completed
        kQueue.Dequeue(&kQueue, NULL);
        if (NULL != callback)
          put_event(FLSH_ID, callback, callback_arg);
      } else                          // otherwise, execute flash I/O
        func(arg);
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

  // Update pgm_size, always return false.
  if (0 != step_size && 0 == pgm_size) {
    pgm_size = step_size;
    return false;
  }
  // Update arg, check completed.
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
    DBG_PRINTF("  flash: invalid address 0x%08lX!\n", base);
    return kFlashInvalidAddr;
  }

  // Update arg new base and limit
  arg->base = priv->base;
  for (; (arg->limit = priv->base+priv->size) < limit; ++priv)
    ;
  return kFlashSuccess;
}

static flash_st check_program_arg(flash_arg_t *arg,
                                uint32_t low_bound, uint32_t up_bound)
{
  uint32_t base = arg->base;
  uint32_t size = arg->limit - arg->base;
  void *src = arg->src;

  if (NULL == flash_priv_get(base)   // find private table
      || low_bound > base            // lower bound
      || up_bound <= base + size     // upper bound
      || 0 != base % kDoubleWord) {
    DBG_PRINTF("  flash: invalid address 0x08%lX!\n", base);
    return kFlashInvalidAddr;
  }
  if (NULL == src) {
    DBG_PRINTF("  flash: NULL pointer!\n");
    return kFlashNullPointer;
  }
  if (0 != size % kDoubleWord) {
#if FLASH_PROGRAM_SIZE_PADDING
    size = ((size + kDoubleWord - 1) / kDoubleWord) * kDoubleWord;
    arg->limit = arg->base + size;
#else
    DBG_PRINTF("  flash: invalid program size aligned 0x%08lX!\n", size);
    return kFlashInvalidSize;
#endif
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

static flash_st pre_flash_erase(flash_arg_t *task_arg)
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

  DBG_PRINTF("  flash: pre erase: 0x%08lX\n", task_arg->base);

  C55FMC.MCR.B.EHV = 1;             // Start internal erase sequence
  return kFlashSuccess;
}

static flash_st pre_flash_program(flash_arg_t *task_arg)
{
  flash_priv_t *priv = flash_priv_get(task_arg->base);
  // Data must be aligned to 64-bit
  uint64_t *dest = (uint64_t *)task_arg->base;
  uint64_t *src = (uint64_t *)task_arg->src;
  // Segment limit is absolute address 128-Byte aligned
  // i.e. cross-segment flash program is not allowed. PEG error.
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

  DBG_PRINTF("  flash: pre program: 0x%08lX, pgm_size: 0x%08lX\n",
         task_arg->base, pgm_size);

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

  DBG_PRINTF("  flash: post erase: 0x%08lX\n", task_arg->base);

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
    DBG_PRINT_REG();
    C55FMC.MCR.B.RWE = 1;         // Reset read-while-write error
    DBG_PRINTF("  flash: erase failed 0x%08lX!\n", task_arg->base);
    return kFlashEraseError;
  }
  return kFlashSuccess;
}

static flash_st post_flash_program(flash_arg_t *task_arg)
{
  flash_priv_rgn_t *prgn = flash_priv_rgn_get(task_arg->base);

  if (NULL == prgn)
    return kFlashInvalidAddr;

  C55FMC.MCR.B.EHV = 0;           // Disable high voltage
  C55FMC.MCR.B.PGM = 0;           // End programming
  C55FMC.MCR.B.PEAS = 0;          // Activate main array space

  DBG_PRINTF("  flash: post program: 0x%08lX\n", task_arg->base);

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
    DBG_PRINT_REG();
    C55FMC.MCR.B.RWE = 1;         // Reset read-while-write error
    DBG_PRINTF("  flash: program failed 0x%08lX!\n", task_arg->base);
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
    flash_erase_bio(dest, 0);
  else if (dest > 0 && src > 0 && data > 0)
    flash_write_bio(dest, (void *)src, (uint32_t)data);
  else if (argc > 3 && dest > 0 && src == 0)
    flash_write64_bio(dest, data);
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
    utest_write_bio(dest, (void *)src, size);
  }
  else if (!strncmp("w64", argv[1], 3) && argc > 3) {
    data = strtoull(argv[3], NULL, 16);
    dest = kPrivRgn[kUTest].base + offs;
    utest_write64_bio(dest, data);
  }
}

static void eeprom_tester(char **argv, int argc)
{
  uint32_t addr;

  if (argc < 2)
    return;

  addr = strtoul(argv[2], NULL, 16);

  if(!strncmp(argv[1], "erase", 5)){
    eeprom_erase_bio(addr, 0);
  }
  else if (!strncmp(argv[1], "write", 5) && argc >= 5){
    uint32_t src = strtoul(argv[3], NULL, 16);
    uint32_t count = strtoul(argv[4], NULL, 16);
    eeprom_write_bio(addr, (void *)src, count);
  }
  else if (!strncmp(argv[1], "wr64", 4) && argc >= 4){
    uint64_t data = strtoll(argv[3], NULL, 16);
    eeprom_write64_bio(addr, data);
  }
}

#if FLASH_DEBUG
static const char *string_of_state(flash_st state)
{
  static const char *state_list[] = {
    "success",
    "ready",
    "isr_ready",
    "bio_busy",
    "nio_busy",
    "safety"
  };

  if (0 > state)
    return '\0';
  else
    return state_list[state];
}

static void flash_print_register(void)
{
  PRINTF("  flash: mcr   register: 0x%08lX\n", C55FMC.MCR.R);
  PRINTF("  flash: mcre  register: 0x%08lX\n", C55FMC.MCRE.R);
  PRINTF("  flash: lock0 register: 0x%08lX\n", C55FMC.LOCK0.R);
  PRINTF("  flash: lock1 register: 0x%08lX\n", C55FMC.LOCK1.R);
  PRINTF("  flash: lock2 register: 0x%08lX\n", C55FMC.LOCK2.R);
  PRINTF("  flash: lock3 register: 0x%08lX\n", C55FMC.LOCK3.R);
  PRINTF("  flash: sel0  register: 0x%08lX\n", C55FMC.SEL0.R);
  PRINTF("  flash: sel1  register: 0x%08lX\n", C55FMC.SEL1.R);
  PRINTF("  flash: sel2  register: 0x%08lX\n", C55FMC.SEL2.R);
  PRINTF("  flash: sel3  register: 0x%08lX\n", C55FMC.SEL3.R);
  PRINTF("  flash: adr   register: 0x%08lX\n", C55FMC.ADR.R);
  PRINTF("  flash: ut0   register: 0x%08lX\n", C55FMC.UT0.R);
  PRINTF("  flash: um0   register: 0x%08lX\n", C55FMC.UM[0].R);
  PRINTF("  flash: um1   register: 0x%08lX\n", C55FMC.UM[1].R);
  PRINTF("  flash: um2   register: 0x%08lX\n", C55FMC.UM[2].R);
  PRINTF("  flash: um3   register: 0x%08lX\n", C55FMC.UM[3].R);
  PRINTF("  flash: um4   register: 0x%08lX\n", C55FMC.UM[4].R);
  PRINTF("  flash: um5   register: 0x%08lX\n", C55FMC.UM[5].R);
  PRINTF("  flash: um6   register: 0x%08lX\n", C55FMC.UM[6].R);
  PRINTF("  flash: um7   register: 0x%08lX\n", C55FMC.UM[7].R);
  PRINTF("  flash: um8   register: 0x%08lX\n", C55FMC.UM[8].R);
  PRINTF("  flash: um9   register: 0x%08lX\n", C55FMC.UM9.R);
  PRINTF("  flash: opp0  register: 0x%08lX\n", C55FMC.OPP0.R);
  PRINTF("  flash: opp1  register: 0x%08lX\n", C55FMC.OPP1.R);
  PRINTF("  flash: opp2  register: 0x%08lX\n", C55FMC.OPP2.R);
  PRINTF("  flash: opp3  register: 0x%08lX\n", C55FMC.OPP3.R);
  PRINTF("  flash: tmd   register: 0x%08lX\n", C55FMC.TMD.R);
}

static void flash_help(void)
{
  PRINTF("----Flash: command----\n");
  PRINTF("  flash erase <addr> <size>\n");
  PRINTF("  flash write <addr> <size>\n");
  PRINTF("  flash write64k <addr>\n");
  PRINTF("  flash first_blank <addr> [<size>]\n");
  PRINTF("  flash rest_blank <addr>\n");
}

static void flash_dump(void)
{
  PRINTF("----Flash: status----\n");
  PRINTF("  state:          %12s\n", string_of_state(kState));
}
#endif

/**************************************************
 * Test                                           *
 **************************************************/
#if FLASH_DEBUG
static void test_console(char **argv, int argc)
{
  static uint8_t buff[kQuadPage] = {0xFF};
  static uint8_t num = 0;
  uint8_t cnt;
  uint32_t base;
  uint32_t size;
  void *src;

  if (argc == 2 && !strcmp(argv[1], "help")) {
    flash_help();
  }
  else if (argc == 2 && !strcmp(argv[1], "show_reg")) {
    flash_print_register();
  }
  else if (argc == 3 && !strcmp(argv[1], "erase") &&
           !strcmp(argv[2], "eeprom")) {
    eeprom_erase_bio(kPriv[1].base, 0);
    eeprom_erase_bio(kPriv[2].base, 0);
    eeprom_erase_bio(kPriv[3].base, 0);
    eeprom_erase_bio(kPriv[4].base, 0);
    PRINTF("  flash debug: erase eeprom done!\n");
  }
  else if ((argc == 3 || argc == 4) &&
           (!strcmp(argv[1], "erase") || !strcmp(argv[1], "erase_bio"))) {
    base = strtoul(argv[2], NULL, 16);
    if (argc == 4)
      size = strtoul(argv[3], NULL, 16);
    else
      size = 0;
    if (!strcmp(argv[1], "erase"))
      flash_erase(base, size, (void (*)(void *))callback_dummy, NULL);
    else
      flash_erase_bio(base, size);
    PRINTF("  flash debug: erase done!\n");
  }
  else if ((argc == 4 || argc == 5) &&
           (!strcmp(argv[1], "write") || !strcmp(argv[1], "write_bio"))) {
    base = strtoul(argv[2], NULL, 16);
    size = strtoul(argv[3], NULL, 16);
    if (size > sizeof(buff))
    	return;
    if (argc == 5)
      cnt = strtoul(argv[4], NULL, 10);
    else
      cnt = 1;
    ++num;
    for (uint32_t i = 0; i < size; ++i)
      buff[i] = num;
    for (uint8_t i = 0; i < cnt; ++i) {
      if (!strcmp(argv[1], "write"))
        flash_write(base, buff, size, (void (*)(void *))callback_dummy, NULL);
      else
        flash_write_bio(base, buff, size);
      base += size;
    }
    PRINTF("  flash debug: write done!\n");
  }
  else if (argc == 3 && (!strcmp(argv[1], "write64k"))) {
    base = strtoul(argv[2], NULL, 16);
    size = 0x10000;
    src = spt_work_space_get();
    PRINTF("spt work space addr: %p\n", src);
    flash_write(base, src, size, (void (*)(void *))callback_dummy, NULL);
    PRINTF("  flash debug: write64k test done!\n");
  }
  else if (argc == 5 && !strcmp(argv[1], "test")) {
    base = strtoul(argv[2], NULL, 16);
    size = strtoul(argv[3], NULL, 16);
    cnt = strtoul(argv[4], NULL, 10);
    ++num;
    for (uint32_t i = 0; i < size; ++i)
      buff[i] = num;
    for (uint32_t i = 0; i < cnt; ++i) {
      flash_write(base, buff, size, (void (*)(void *))callback_dummy, NULL);
      base += size;
    }
    flash_erase_bio(base, size);
    flash_write_bio(base, buff, size);
    PRINTF("  flash debug: test done!\n");
  }
  else if (argc == 3 && !strcmp(argv[1], "next_blk")) {
    src = (void *)strtoul(argv[2], NULL, 16);
    if (kFlashSuccess == flash_next_blk((const void **)&src))
      PRINTF("  flash next block: %p\n", src);
  }
  else if (argc == 3 && !strcmp(argv[1], "rest_blank")) {
    base = strtoul(argv[2], NULL, 16);
    if (is_flash_rest_blk_blank(base))
      PRINTF("  flash reset of block is blank, from: %p\n", (void *)base);
  }
  else if ((argc == 3 || argc == 4) && !strcmp(argv[1], "first_blank")) {
    src = (void *)strtoul(argv[2], NULL, 16);
    if (argc == 3)
      size = kSinglePage;
    else if (argc == 4)
      size = strtoul(argv[3], NULL, 16);
    if (kFlashSuccess == flash_first_blank_segment((const void **)&src, size, 0))
      PRINTF("  flash first blank: %p\n", src);
  }
#if FLASH_DEBUG && FLASH_READ
  else if ((argc == 3 || argc == 4) && !strcmp(argv[1], "read")) {
    base = strtoul(argv[2], NULL, 16);
    if (argc == 4)
      size = strtoul(argv[3], NULL, 16);
    else
      size = kQuadPage;
    flash_read(base, size);
    PRINTF("  flash debug: read done!\n");
  }
#endif
  else if (argc == 3 && !strcmp(argv[1], "rweb")) {  // reset_while_erase_bio
    base = strtoul(argv[2], NULL, 16);
    flash_arg_t task = {.base = base, .limit = base, .src = NULL};
    pre_flash_erase(&task);
    while (0 == C55FMC.MCR.B.DONE) {
#ifdef ENABLE_SWT
      clear_SWT0_counter();
#endif
      fs8x_wd_handle(fs8xFlash);
#if FLASH_DEBUG
    Delay_ms(100);
    reset_system();
#endif
    }
    post_flash_erase(&task);
  }
  else if (argc == 3 && !strcmp(argv[1], "rwwb")) {  // reset_while_write_bio
    base = strtoul(argv[2], NULL, 16);
    flash_arg_t task = {.base = base, .limit = sizeof(buff), .src = buff};
    pre_flash_program(&task);
    while (0 == C55FMC.MCR.B.DONE) {
#ifdef ENABLE_SWT
      clear_SWT0_counter();
#endif
      fs8x_wd_handle(fs8xFlash);
#if FLASH_DEBUG
    Delay_us(100);
    reset_system();
#endif
    }
    post_flash_program(&task);
  }
  else {
    flash_dump();
  }
}

static void callback_dummy(void)
{
  static uint8_t i = 0;
  PRINTF("  flash debug: callback dummy - Hello World!  %u\n", ++i);
}
#endif
