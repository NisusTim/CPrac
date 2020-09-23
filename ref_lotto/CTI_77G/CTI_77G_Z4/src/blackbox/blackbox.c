#include <stdbool.h>
#include <stdlib.h>       // rand()
#include <string.h>       // memset()
#include "blackbox.h"
#include "flash.h"
#include "timer.h"        // time_get(), DEFAULT_TICKS_PER_SECOND
#include "console_api.h"  // PRINTF()
#include "console_cmd.h"  // console_command_reg()
#include "console.h"      // put_string()
#include "sbc_fs8x.h"     // fs8x_wd_handle()
#include "SWT.h"          // clear_SWT0_counter()

#define STR(x)          #x
#define CUBTEK_ID       STR(Cub.Inc)
#define BLOCK_CAP       3  // 0x00FD0000, 0x00FE0000, 0x00FF0000
#define FLASH_BIO       1
#if FLASH_BIO == 1
#define FLASH_WRITE(addr, src, size)  flash_write_bio(addr, src, size);
#define FLASH_ERASE(addr, size)       flash_erase_bio(addr, size);
#else
#define FLASH_WRITE(addr, src, size)  flash_write(addr, src, size, NULL, NULL);
#define FLASH_ERASE(addr, size)       flash_erase(addr, size, NULL, NULL);
#endif

enum _BlackBoxPrivateConst {
  kPayload     = 0x0,
  kHead        = 0x1,
  k3bitMask    = 0x7,
  k4bitMask    = 0xF,
};

typedef struct _Block {
  blk64k_t reserved[1];
} blk_t;

// @counter: 0 to (UINT16_MAX - 1), starts from 0, the ordering of block
// @timestamp: 0 to (UINT32_MAX - 1), time tick relative to tick obj init-ed
//   since time tick 4.17 ms in uint32_t, limit ~= 200 days
//   no need for dealing with overflow
typedef struct _Recorder {
  page_flag_t flag;
  uint8_t     CubTek_ID[7];
  uint16_t    counter;
  uint16_t    frm_num;
  uint8_t     reserved[15];
  uint8_t     checksum;
  uint32_t    timestamp;
} rec_t;

/**************************************************
 * Forward Declarations                           *
 **************************************************/
// APIs
void InitBlackBox(BlackBox *self, uint8_t tick_ms);
// write data into flash
static void Record(BlackBox *self, uint8_t to_sync_time, uint8_t half_flag);
static void Countdown(BlackBox *self, uint16_t final_sec);
static void ResetCountdown(BlackBox *self);
static void Dump(BlackBox *self);

// Private Methods
static void TransitState(BlackBox *self, bbox_st);
static void RestoreState(BlackBox *self);
static void InitRecord(BlackBox *self);
static void RecordPage(BlackBox *self, uint8_t, uint8_t);
static void write_rec(BlackBox *self, io_mode_t);
static void write_page(BlackBox *self, uint8_t, io_mode_t);
static bool erase_if_border_reached(BlackBox *self);
static void RenewLeftSec(BlackBox *self, uint16_t);
static void RenewLatestRec(const rec_t **, uint16_t *);
static void RenewLatestPage(const page_t **, const rec_t *, uint8_t *);
static void RenewCursorPage(const page_t **, const page_t *, const rec_t *);
static void next_block_head_acyclic(const blk_t **);
static void next_block_head(const blk_t **);
static void next_page(const page_t **);
static inline bool IsRec(const void *);
static inline bool IsPage(const void *);
static bool is_border_reached(const uint32_t);
static uint8_t calculate_xor_checksum(uint8_t *, uint32_t);
#if BLACKBOX_DEBUG
static void DumpFlash(void);
static void TestConsole(char **, int);
#endif

/**************************************************
 * Globals                                        *
 **************************************************/
extern blk64k_t kBlackBox[];
blk_t *kBlocks = (blk_t *)kBlackBox;
static uint32_t *kBase;      // valid start address of blackbox
static uint32_t *kLimit;     // valid end address of blackbox
static uint32_t kSize;       // whole memory size b/w kBase and kLimit
static uint8_t kBlockCap;    // block capacity for blackbox
static uint32_t kBlockSize;  // kSize / FLASH_BLOCK_CAP
static uint16_t kPageCap;    // kBlockSize / PAGE_SZ, page capacity per block
static const rec_t *kLatestRec;    // latest record of previous run
static const page_t *kLatestPage;  // latest page of previous run
static const page_t *kCursorPage;  // recording cursor, be determined by kLatestPage
static page_t kBuffToWrite;
// unit conversion factor
static const double kTick2Sec = 1.0 / DEFAULT_TICKS_PER_SECOND;  // 0.00417 s
static double kPageTick2Sec = PAGE_TIME_UNIT_MS / 1000.0;        // 0.050   s
#if BLACKBOX_DEBUG
static BlackBox *kObj;
static const page_t *kHeadPage;    // start address for dumping
#endif

/**************************************************
 * APIs                                           *
 **************************************************/
void InitBlackBox(BlackBox *self, uint8_t tick_ms)
{
  // init globals
  kBase = (uint32_t *)kBlocks;
  kLimit = (uint32_t *)&kBlocks[kBlackboxBlockCap];
  kSize = (uint32_t)kLimit - (uint32_t)kBase;
  kBlockCap = BLOCK_CAP;
  kBlockSize = kSize / kBlackboxBlockCap;
  kPageCap = kBlockSize / PAGE_SZ;
  kLatestRec = (const rec_t *)kBase;
  kLatestPage = (const page_t *)kBase;
  kCursorPage = (const page_t *)kBase;
  kPageTick2Sec = tick_ms ? (tick_ms/1000.0) : kPageTick2Sec;
  // init BlackBox instance
  self->curr_state = kBBoxReady;  // initial status: kReady
  self->prev_state = kBBoxReady;
  self->left_sec = 0.0f;
  self->Record = Record;
  self->Countdown = Countdown;
  self->ResetCountdown = ResetCountdown;
  self->Dump = Dump;
  // only init here, benchmark of recorders
  self->tm_stamp_new_obj_ = time_get();
  self->tm_stamp_new_rec_ = self->tm_stamp_new_obj_;  // benchmark of page
  self->tm_stamp_left_sec_ = self->tm_stamp_new_obj_;
  self->rec_counter_ = 0;
  InitRecord(self);
#if BLACKBOX_DEBUG
  kObj = self;
  kHeadPage = (page_t *)kBase;
  console_command_reg("blackbox", TestConsole);
#endif
}

static void Record(BlackBox *self, uint8_t to_sync_time, uint8_t half_flag)
{
  switch (self->curr_state) {
    case kBBoxInitError:
      return;
      break;
    case kBBoxReady:
      TransitState(self, kBBoxRecording);
#if BLACKBOX_DEBUG
      kHeadPage = kCursorPage;
#endif
      self->Record(self, to_sync_time, half_flag);
      break;
    case kBBoxRecording:
      RecordPage(self, to_sync_time, half_flag);
      break;
    case kBBoxCountdown:
      RenewLeftSec(self, 0);
      if (0.0f >= self->left_sec) {           // case of time up
        TransitState(self, kBBoxSleeping);
      } else if (0.0f < self->left_sec) {     // case of countdown
        RecordPage(self, to_sync_time, half_flag);
      }
      break;
    case kBBoxBusyErasing:
      if (!is_flash_io_done()) {              // case of busy I/O
        return;
      } else {                                // case of new block
        RestoreState(self);
        RecordPage(self, to_sync_time, half_flag);
      }
      break;
    default:
      break;
  }
}

static void Countdown(BlackBox *self, uint16_t final_sec)
{
  switch (self->curr_state) {
    case kBBoxInitError:
      return;
      break;
    case kBBoxRecording:
      TransitState(self, kBBoxCountdown);
      RenewLeftSec(self, final_sec);
      break;
    case kBBoxCountdown:
      RenewLeftSec(self, final_sec);
      break;
    default:
      break;
  }
}

static void ResetCountdown(BlackBox *self)
{
  switch (self->curr_state) {
    case kBBoxInitError:
      return;
      break;
    case kBBoxCountdown:
      TransitState(self, kBBoxRecording);
      break;
    case kBBoxSleeping:
      TransitState(self, kBBoxReady);
      break;
    default:
      break;
  }
}

static void Dump(BlackBox *self)
{
  ;
}

/**************************************************
 * Private Methods                                *
 **************************************************/
static void TransitState(BlackBox *self, bbox_st new_state)
{
  self->prev_state = self->curr_state;
  self->curr_state = new_state;
}

static void RestoreState(BlackBox *self)
{
  bbox_st temp = self->curr_state;
  self->curr_state = self->prev_state;
  self->prev_state = temp;
}

static void InitRecord(BlackBox *self)
{
  // First init case, to scan the flash memory blocks.
  // and renew kLatestBlk, kLatestPage, kCursorPage.
  RenewLatestRec(&kLatestRec, &self->rec_counter_);
  RenewLatestPage(&kLatestPage, kLatestRec, &self->curr_state);
  RenewCursorPage(&kCursorPage, kLatestPage, kLatestRec);
  PRINTF("BlackBox: Init: kLatestRec: %p, kLatestPage: %p, kCursorPage: %p\n",
         kLatestRec, kLatestPage, kCursorPage);

  if (NULL != kCursorPage) {
    write_rec(self, kBlocking);
    self->tm_stamp_new_page_ = time_get();
    if (erase_if_border_reached(self))
      return;
  } else {
    TransitState(self, kBBoxInitError);
  }
}

static void RecordPage(BlackBox *self, uint8_t to_sync_time, uint8_t half_flag)
{
  int64_t delta_t;
  uint32_t cursor_addr;

  // To synchronize time tick
  if (to_sync_time) {
    self->tm_stamp_new_page_ = time_get();
    delta_t = self->tm_stamp_new_page_ - self->tm_stamp_new_rec_;
    // Overflow of page->rel_time, write a new rec_t
    if (UINT16_MAX * kPageTick2Sec / kTick2Sec <= delta_t || 0 > delta_t) {
      write_rec(self, kNonBlocking);
      self->tm_stamp_new_page_ = time_get();
      erase_if_border_reached(self);
    }
  }

  // Block is full, write a new rec_t
  cursor_addr = (uint32_t)kCursorPage;
  if (is_border_reached(cursor_addr)) {
    write_rec(self, kNonBlocking);
    self->tm_stamp_new_page_ = time_get();
  }
  write_page(self, half_flag, kNonBlocking);
  erase_if_border_reached(self);
}

static void write_rec(BlackBox *self, io_mode_t mode)
{
  const uint32_t size_to_write = PAGE_SZ;
  const uint32_t addr_to_write = (uint32_t)kCursorPage;  // nec variable to hold addr
  rec_t *rec = (rec_t *)&kBuffToWrite;

//  // Renew kLatestRec, kCursorPage address.
//  kLatestRec = (const rec_t *)addr_to_write;
//  next_page(&kCursorPage);

  // Renew obj, obj's rec_buff and write into flash.
  self->tm_stamp_new_rec_ = time_get();
  self->rec_counter_ = (self->rec_counter_ + 1) % (kFlashBlank & UINT16_MAX);
  rec->flag.head = 1;
  rec->flag.state = self->curr_state & k3bitMask;
  rec->flag.reserved = 0;
  // Assignment prior to counter: overwrite uint8_t CubTek_ID[7] = '\0'
  memcpy((char *)rec->CubTek_ID, CUBTEK_ID, sizeof(rec->CubTek_ID));
  rec->counter = self->rec_counter_;
  rec->frm_num = self->frm_num;
  memset(rec->reserved, 0, sizeof(rec->reserved));
  rec->timestamp = (self->tm_stamp_new_rec_ - self->tm_stamp_new_obj_)
                   * kTick2Sec / kPageTick2Sec;
  rec->checksum = calculate_xor_checksum((uint8_t *)rec, sizeof(rec_t));
  switch (mode) {
    case kBlocking:
      flash_write_bio(addr_to_write, rec, size_to_write);
      break;
    case kNonBlocking:
      flash_write(addr_to_write, rec, size_to_write, NULL, NULL);
      break;
    default:
      break;
  }

  // Renew kLatestRec, kCursorPage address.
  kLatestRec = (const rec_t *)addr_to_write;
  next_page(&kCursorPage);
  PRINTF("BlackBox: write_rec: 0x%08lX, next_page kCursorPage: %p\n", addr_to_write, kCursorPage);
}

static void write_page(BlackBox *self, uint8_t half_flag, io_mode_t mode)
{
  const uint32_t size_to_write = PAGE_SZ;
  const uint32_t addr_to_write = (uint32_t)kCursorPage;
  page_t *page = (page_t *)&kBuffToWrite;

//  // Renew kLatestPage, kCursorPage address.
//  kLatestPage = (const page_t *)addr_to_write;
//  next_page(&kCursorPage);

  // Renew obj's page_buff and write into flash.
  memcpy(page, &self->rec_buff, sizeof(page_t));
  page->flag.head = 0;
  page->flag.state = self->curr_state & k3bitMask;
  page->rel_time = (self->tm_stamp_new_page_ - self->tm_stamp_new_rec_)
                   * kTick2Sec / kPageTick2Sec;
  page->flag.reserved = half_flag & k4bitMask;
  switch (mode) {
    case kBlocking:
      flash_write_bio(addr_to_write, page, size_to_write);
      break;
    case kNonBlocking:
      flash_write(addr_to_write, page, size_to_write, NULL, NULL);
      break;
    default:
      break;
  }

  // Renew kLatestPage, kCursorPage address.
  kLatestPage = (const page_t *)addr_to_write;
  next_page(&kCursorPage);
  PRINTF("BlackBox: write_page: 0x%08lX, next_page kCursorPage: %p\n", addr_to_write, kCursorPage);
}

static bool erase_if_border_reached(BlackBox *self)
{
  const uint32_t addr_to_erase = (uint32_t)kCursorPage;  // nec variable to hold addr

  // if nearly reached
  if (is_border_reached(addr_to_erase)) {
    TransitState(self, kBBoxBusyErasing);
    FLASH_ERASE((uint32_t)addr_to_erase, 0);
    PRINTF("BlackBox: Erase: 0x%08lX\n", addr_to_erase);
    return true;
  }

  return false;
}

static void RenewLeftSec(BlackBox *self, uint16_t final_sec)
{
  uint32_t stamp = time_get();

  self->left_sec -= (float)(stamp - self->tm_stamp_left_sec_) * kTick2Sec;
  if (0 < final_sec && 0 >= self->left_sec)
    self->left_sec = (float)final_sec;
  else if (0 < final_sec && final_sec < self->left_sec)
    self->left_sec = (float)final_sec;

  self->tm_stamp_left_sec_ = stamp;
}

static void RenewLatestRec(const rec_t **latest, uint16_t *rec_cnt)
{
  if (NULL == latest || NULL == rec_cnt)
    return;

  const rec_t *base = (const rec_t *)kBase;
  const rec_t *limit = (const rec_t *)kLimit;
  const rec_t *curr = base;
  const rec_t *prev = base;
  const rec_t *thru;
  const rec_t *result = NULL;

  // Find the first rec_t, then break
  for (thru = base; thru < limit; ++thru) {
    if (IsRec(thru)) {  // case of only-one-head
      result = curr = prev = thru;
      break;
    } else if (IsPage((const page_t *)thru)) {
      ;
    } else {
      next_block_head_acyclic((const blk_t **)&thru);
      --thru;
    }
  }
  // Find rec_t with the max or discrete counter
  for (++thru; thru < limit; ++thru) {
    if (IsRec(thru)) {
      prev = curr;
      // Case of max, use curr as result
      result = curr = thru;
      // Case of discrete, use prev as result
      if (curr->counter != (prev->counter + 1) % UINT16_MAX) {
        result = prev;
        break;
      }
    } else if (IsPage((const page_t *)thru)) {
      ;
    } else {
      next_block_head_acyclic((const blk_t **)&thru);
      --thru;
    }
  }

  // Case of the latest rec_t found
  if (NULL != result) {
    *latest = result;
    *rec_cnt = (*latest)->counter;
  // Case of not found
  } else {
    *latest = NULL;
    *rec_cnt = 0;
  }
}

static void RenewLatestPage(const page_t **latest, const rec_t *start_rec, uint8_t *state)
{
  if (NULL == latest)
    return;
  else if (NULL == start_rec) {
    *latest = NULL;
    return;
  }

  const page_t *base = (const page_t *)start_rec;
  const page_t *limit = (const page_t *)start_rec;
  const page_t *result = NULL;

  // base would be next page of start_rec
  next_page(&base);

  // Case of invalid address of rec_t
  // limit would be end of block of start_rec
  if (kFlashSuccess != flash_end_of_blk((const void **)&limit)) {
    *latest = NULL;
    return;
  }

  // Find the latest page
  for (const page_t *thru = base; thru < limit; ++thru) {
    if (IsPage(thru))
      result = thru;
    else {
      next_block_head_acyclic((const blk_t **)&thru);
      --thru;
    }
  }

  // Case of found or not found
  *latest = result;

  // Renew obj's curr_state
  if (NULL != *latest && NULL != state &&
      (kFlashBlank & UINT32_MAX) != *(uint32_t *)(*latest)) {
    switch ((*latest)->flag.state) {
      case kBBoxCountdown:
      case kBBoxSleeping:
        *state = kBBoxSleeping;
        break;
      default:
        *state = kBBoxReady;
        break;
    }
  }
}

static void RenewCursorPage(const page_t **cursor, const page_t *start_page, const rec_t *start_rec)
{
  uint8_t check_block_cnt;

  if (NULL == cursor)
    return;
  else if (NULL != start_page) {
    *cursor = start_page;
    check_block_cnt = 1;
  } else if (NULL != start_rec) {
    *cursor = (const page_t *)start_rec;
    check_block_cnt = 1;
  } else {
    *cursor = (const page_t *)kBase;
    check_block_cnt = kBlockCap;
  }

  for (uint8_t i = 0; i < check_block_cnt; ++i) {
    // Find a blank and the rest block blank, return
    if (kFlashSuccess == flash_first_blank_segment((const void **)cursor, sizeof(page_t), sizeof(page_t))
        && is_flash_rest_blk_blank((uint32_t)*cursor)) {
      PRINTF("BlackBox: *cursor");
      return;
    }
    next_block_head((const blk_t **)cursor);
  }

  for (uint8_t i = 0; i < kBlockCap; ++i) {
    // Erase a new block, return
    if (kFlashSuccess == flash_erase_bio((uint32_t)*cursor, 0)) {
      PRINTF("BlackBox: Erase: %p\n", *cursor);
      return;
    }
    next_block_head((const blk_t **)cursor);
  }

  // No blank and erasing failed
  *cursor = NULL;
}

static void next_block_head_acyclic(const blk_t **blk)
{
  if (NULL == blk)
    return;

  if (kFlashSuccess != flash_next_blk((const void **)blk)) {
    PRINTF("BlackBox: next_block: %p, kCursorPage: %p\n", *blk, kCursorPage);
    return;
  }
}

static void next_block_head(const blk_t **blk)
{
  next_block_head_acyclic(blk);

  const blk_t *base = (const blk_t *)kBase;
  const blk_t *limit = (const blk_t *)kLimit;

  if (limit <= *blk) {
    *blk = base;
    PRINTF("BlackBox: next_block: %p, kCursorPage: %p\n", *blk, kCursorPage);
  }
}

static void next_page(const page_t **page)
{
  if (NULL == page)
    return;

  const page_t *base = (const page_t *)kBase;
  const page_t *limit = (const page_t *)kLimit;

  if (limit <= ++*page)
    *page = base;
}

static inline bool IsRec(const void *ptr)
{
  if (NULL == ptr)
    return false;

  const rec_t *rec = (const rec_t *)ptr;
/*
  if (0 == strcmp((char *)rec->CubTek_ID, CUBTEK_ID)) && 1 == rec->flag.head
      && 0 == calculate_xor_checksum((uint8_t *)rec, sizeof(rec_t)))
    return true;
  else
    return false;
    */
  if (0 != memcmp((char *)rec->CubTek_ID, CUBTEK_ID, sizeof(rec->CubTek_ID))) {
    //PRINTF("BlackBox: IsRec() strcmp id error: %s\n", (char *)rec->CubTek_ID);
    return false;
  }
  if (1 != rec->flag.head) {
    //PRINTF("BlackBox: IsRec() rec->flag not head: %u\n", rec->flag.head);
    return false;
  }
  if (0 != calculate_xor_checksum((uint8_t *)rec, sizeof(rec_t))) {
    PRINTF("BlackBox: IsRec() checksum error: %p\n", rec);
    return false;
  }

  return true;
}

static inline bool IsPage(const void *ptr)
{
  if (NULL == ptr)
    return false;

  const page_t *page = (const page_t *)ptr;

  if ((kFlashBlank & UINT16_MAX) != page->rel_time && 0 == page->flag.head)
    return true;
  else
    return false;
}

static bool is_border_reached(const uint32_t addr)
{
  if (0 == addr)
    return false;

  uint32_t relative = (uint32_t)addr - (uint32_t)kBase;

  if (0 == relative % kBlockSize && kBlackboxBlockCap > relative / kBlockSize)
    return true;
  else
    return false;
}

static uint8_t calculate_xor_checksum(uint8_t *ptr, uint32_t size)
{
  if (NULL == ptr)
    return 0xFF;

  uint8_t result = 0xFF;

  for (uint32_t i = 0; i < size; ++i)
    result ^= *ptr++;

  return result;
}

/**************************************************
 * Test                                           *
 **************************************************/
#if BLACKBOX_DEBUG
static void DumpFlash(void)
{
  uint32_t base = (uint32_t)kBase;
  uint32_t limit = (uint32_t)kLimit;
  uint32_t start = (uint32_t)kHeadPage;
  uint32_t end = (uint32_t)kCursorPage;

  PRINTF("----BlackBox: dump flash data----\n");
  if ((void *)kCursorPage > (void *)kHeadPage) {
    flash_read(start, end);
  } else {
    flash_read(start, limit);
    flash_read(base, end);
  }
}

static void TestConsole(char **argv, int argc)
{
  if (argc == 2 && !strcmp(argv[1], "dump")) {
    DumpFlash();
  } else {
    PRINTF("----BlackBox: status----\n");
    PRINTF("  frm_num: 0x%04X\n", kObj->frm_num);
    PRINTF("  curr_state: %u;  prev_state: %u;  left_sec: %6.2f ms;"
           "  rec_counter: 0x%04X\n",
           kObj->curr_state, kObj->prev_state, kObj->left_sec,
           kObj->rec_counter_);
    PRINTF("  CursorPage: %p;  HeadPage: %p;  LatestPage: %p\n",
           kCursorPage, kHeadPage, kLatestPage);
    PRINTF("  --BlackBox: timer--\n");
    PRINTF("  tick unit: %3.0f ms\n", kPageTick2Sec * 1000);
    PRINTF("  obj: 0x%08lX;  rec: 0x%08lX;  page: 0x%08lX;  left: 0x%08lX\n",
           kObj->tm_stamp_new_obj_, kObj->tm_stamp_new_rec_,
           kObj->tm_stamp_new_page_, kObj->tm_stamp_left_sec_);
  }
}
#endif
