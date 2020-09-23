/*
 * flash.h
 *
 *  Created on: 2017-08-24
 *      Author: erichu
 *  Refined on: 2019-11-15
 *   Co-Author: timchang
 */
#ifndef FLASH_H_
#define FLASH_H_

#include <stdbool.h>
#include <stdint.h>

#define FLASH_DEBUG                0
#define FLASH_READ                 0
#define FLASH_PROGRAM_SIZE_PADDING 1
#define DBG_PRINTF(...)  do { if (FLASH_DEBUG) PRINTF(__VA_ARGS__); } while (0)
#if FLASH_DEBUG
#define DBG_PRINT_REG()  flash_print_register()
#else
#define DBG_PRINT_REG()  do { } while (0)
#endif

// for the caller parameter.c
#define EE_ADDR_PARAS_START0  0x00800000
#define EE_ADDR_PARAS_START1  0x00804000
#define SIZE_OF_EE_MEM_BLOCK  0x4000
//                           base,       size
// parameter block1   {0x00800000,    0x04000}
// parameter block2   {0x00804000,    0x04000}
// blackbox block1    {0x00FD0000,    0x10000}
// blackbox block2    {0x00FE0000,    0x10000}
// blackbox block3    {0x00FF0000,    0x10000}
// Z4  image_header   {0x01000000,    0x00080}
// Z4  m_text         {0x01000080,    0xBFF80}
// Z70 image_header   {0x010C0000,    0x00080}
// Z70 m_text         {0x010C0080,    0x7FF80}
// Z71 image_header   {0x01140000,    0x00080}
// Z71 m_text         {0x01140080,    0x3FF70}

enum _FlashPublicConst {
  kBlackboxBlockCap =                  3,
  kEepromBlockCap   =                  2,
  kFlashBlank       = 0xFFFFFFFFFFFFFFFF
};

typedef enum _IoMode {
  kNonBlocking    = 0x01,
  kBlocking       = 0x02
} io_mode_t;

typedef enum _FlashState{
  // State for state machine.
  kFlashSafety       =  5,  // Low voltage protection, program/erase forbidden.
  kFlashNioBusy      =  4,  // Performing non-blocking I/O.
  kFlashBioBusy      =  3,  // Performing blocking I/O.
  kFlashIsrReady     =  2,  // Short period of transition, not used.
  kFlashReady        =  1,  // Default state.
  // Error code for exception handling.
  kFlashSuccess      =  0,  // No error.
  kFlashProgramError = -1,  // Program failed.
  kFlashEraseError   = -2,  // Erase failed.
  kFlashInvalidAddr  = -3,  // Invalid address.
  kFlashInvalidSize  = -4,  // Invalid written size.
  kFlashNullPointer  = -5,  // Invalid written source.
  kFlashQueueOverrun = -6,  // Queue is full.
  kFlashIoBusy       = -7,  // Flash controller is processing. ISR not allowed.
  kFlashAbnormal     = -8   // Case of NOT supposed to be.
} flash_st;

typedef enum _FlashProgramSize {
  kDoubleWord     = 0x08,
  kSinglePage     = 0x20,
  kDualPage       = 0x40,
  kQuadPage       = 0x80,
  kUTestProgSize  = kSinglePage,
  kEepromProgSize = kSinglePage
} flash_prog_size_t;

typedef struct _Block16KiB{
  uint8_t reserved[0x4000];
} blk16k_t;

typedef struct _Block64KiB{
  uint8_t reserved[0x10000];
} blk64k_t;

// flash_erase: 64-KiB block, ~355 ms @indoor temperature
// flash_write: 128 Byte,     ~270 us @indoor temperature
//
void flash_init(void);
void flash_isr(void);
bool is_flash_on_safety(void);
flash_st flash_get_state(void);
flash_st flash_set_safety(bool safety_toggle);  // true: set; false: reset
// Flash API
flash_st flash_erase(uint32_t addr, uint32_t size,
                     void (*callback)(void *), void *callback_arg);
flash_st flash_write(uint32_t addr, void *src, uint32_t size,
                     void (*callback)(void *), void *callback_arg);
flash_st flash_write64(uint32_t addr, uint64_t data,
                       void (*callback)(void *), void *callback_arg);
flash_st flash_erase_bio(uint32_t addr, uint32_t size);
flash_st flash_write_bio(uint32_t addr, void *src, uint32_t size);
flash_st flash_write64_bio(uint32_t addr, uint64_t data);
// UTEST API
flash_st utest_write_bio(uint32_t addr, void *src, uint32_t size);
flash_st utest_write64_bio(uint32_t addr, uint64_t data);
// EEPROM API
flash_st eeprom_erase(uint32_t addr, uint32_t size,
                      void (*callback)(void *), void *callback_arg);
flash_st eeprom_write(uint32_t addr, void *src, uint32_t size,
                      void (*callback)(void *), void *callback_arg);
flash_st eeprom_write64(uint32_t addr, uint64_t data,
                        void (*callback)(void *), void *callback_arg);
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
flash_st flash_read(uint32_t addr, uint32_t size);
#endif

#endif  // FLASH_H_
