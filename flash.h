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

#define FLASH_DEBUG  1

// for the caller parameter.c
#define EE_ADDR_PARAS_START0  0x00800000
#define EE_ADDR_PARAS_START1  0x00804000
#define SIZE_OF_EE_MEM_BLOCK  0x4000

enum _FlashPublicConst {
  kBlackboxBlockCap =          3,
  kEepromBlockCap   =          2,
  kFlashBlank       = 0xFFFFFFFF,
};

typedef enum _FlashState{
  // State for state machine.
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
  kEepromProgSize = kSinglePage,
} flash_prog_size_t;

typedef struct _Block16KiB{
  uint8_t reserved[0x4000];
} blk16k_t;

typedef struct _Block64KiB{
  uint8_t reserved[0x10000];
} blk64k_t;

// flash_erase: 64-KiB block, ~355 ms @indoor temperature
// flash_write: 128 Byte,     ~270 us @indoor temperature
// Note:
//   Memory size of flash_write can NOT be larger than 0x800 byte at one time.
//
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
flash_st flash_dump(uint32_t start, uint32_t end);
#endif

#endif  // FLASH_H_
