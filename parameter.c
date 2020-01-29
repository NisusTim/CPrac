#include <stdbool.h>
#include <string.h>  // strcmp()
#include "parameter.h"
#include "vm_seg.h"

#include <stdio.h>
#include <unistd.h>

enum {
  kParamCap   = kMemCap,
  kEepromSize = 0x8000,
  kRamSize    = 0x2000,
  //kBlankSize  = UINTPTR_MAX,
  kBlankSize  = 0,
  kSealed     = 0x8778887777889487,
  kEmptyName  = 0x00000000
};

typedef struct _PARAMETER_HEADER {  // header in eeprom
  char       name[4];   // 4
                        // 4 auto padding, version?
  UINTPTR_T  size;      // 8
  uint64_t   seal;      // 8
  UINTPTR_T  cksum;     // 8
} param_hdr_t;

typedef struct _PARAMETER_REGISTER_RAM {
  char  name[4];  // name of param
  void *ptr;      // pointer to base address of segmentation in RAM.
} param_reg_t;

/************************************************
 * Forward Declarations                         *
 ************************************************/
void param_init(void);
void *param_reg(char *name, UINTPTR_T pld_size);
bool param_unreg(char *name);
void param_write(char *name);
static param_reg_t *param_reg_get(char *);
static param_reg_t *param_reg_get_empty(void);
static void param_eeprom_copy(void);
static UINTPTR_T *param_cursor_renew(void);
static UINTPTR_T cksum_cal(UINTPTR_T *arr, UINTPTR_T size);
#if PARAMETER_DEBUG
static void param_print(void);
static void eeprom_make(void);
static void eeprom_print(void);
static void ram_print(void);
#endif

/************************************************
 * Globals                                      *
 ************************************************/
static uint8_t kEeprom[kEepromSize] = {0};
static UINTPTR_T const kBase = (UINTPTR_T const)kEeprom;
static UINTPTR_T const kLimit = (UINTPTR_T const)(kEeprom + kEepromSize);
static UINTPTR_T kBlkCursor;
static UINTPTR_T kCursor = (UINTPTR_T)kEeprom;
static uint8_t kRam[0x2000];
static VmSeg kVm;
static param_reg_t kRegTable[kParamCap] = {0};

int main(void)
{
  eeprom_make();
  eeprom_print();
  param_init();

  param_print();
  ram_print();

  param_unreg("01st");
  param_print();
  ram_print();
  // mem_chain_dump(kVm.mem_priv.head);
  // mem_priv_dump(&kVm.mem_priv);
  void *a = param_reg("01st", 0x40);
  memcpy(a, (void *)"0123456789012345678901234567890123456789", 40);
  param_write("01st");
  param_print();
  ram_print();
  /*printf("addr: 0x%08lX, 0x%08lX\n", (UINTPTR_T)(a-0x20), (UINTPTR_T)(a));*/
  /*printf("cksum: 0x%08lX\n", cksum_cal((UINTPTR_T *)(a-0x20), 0x60));*/
  // mem_chain_dump(kVm.mem_priv.head);
  // mem_priv_dump(&kVm.mem_priv);

  /*
  char name[4] = {0};
  printf("char[]: %s\n", (char *)"\0\0\0\0");
  printf("uint32_t: %X\n", *(uint32_t *)"\0\0\0\0");
  uint32_t i = 0x00000000;
  printf("%s\n", (char *)&i);
  printf("%X\n", *(uint32_t *)&i);
  */
}

/************************************************
 * APIs                                         *
 ************************************************/
void param_init(void)
{
  // RAM: init virtual memory
  //      copy EEPROM unsealed to RAM
  InitVmSeg(&kVm, (void *)kRam, sizeof(kRam));
  param_eeprom_copy();
  // EEPROM: renew cursor
  /*param_cursor_renew();*/
}

// @size: payload size
// @return: base address of payload or NULL
void *param_reg(char *name, UINTPTR_T pld_size)
{
  param_reg_t *reg;
  
  // if registered name does exists.
  if (NULL != (reg = param_reg_get(name)))
    return (void *)(reg->ptr + sizeof(param_hdr_t));
  // if not exists but has space then new it and allocate RAM.
  else if (NULL != (reg = param_reg_get_empty()) &&
    NULL != kVm.MAlloc(&kVm, sizeof(param_hdr_t) + pld_size, &reg->ptr)) {
    // init param_reg_t
    strcpy(reg->name, name);
    // init param_hdr_t of param_reg_t
    param_hdr_t *ram_hdr = (param_hdr_t *)reg->ptr;
    strcpy(ram_hdr->name, name);
    ram_hdr->size = sizeof(param_hdr_t) + pld_size;
    return (void *)(reg->ptr + sizeof(param_hdr_t));
  }
  return NULL;
}

bool param_unreg(char *name)
{
  param_reg_t *reg = param_reg_get(name);

  if (NULL != reg) {
    kVm.Free(&kVm, reg->ptr);
    memset(reg, 0x00, sizeof(param_reg_t));
    return true;
  }
  return false;  // not exists
}

void param_write(char *name)
{
  param_reg_t *reg = param_reg_get(name);

  if (NULL != reg) {
    param_hdr_t *ram_hdr = (param_hdr_t *)reg->ptr;
    ram_hdr->cksum = cksum_cal((UINTPTR_T *)ram_hdr, ram_hdr->size);
    // eeprom_write();
  }
  return;
}

/************************************************
 * Private Methods                              *
 ************************************************/
// find existing (param_reg_t *) from reg table.
static param_reg_t *param_reg_get(char *name)
{
  const param_reg_t *base = kRegTable;
  const param_reg_t *limit = &kRegTable[kParamCap];

  // find if exist then return it.
  for (param_reg_t *thru = (param_reg_t *)base; thru < limit; ++thru)
    if (!strcmp(name, thru->name))
      return thru;
  // find if an empty space then return it.
  return NULL;
}

// find empty (param_reg_t *) from reg table.
static param_reg_t *param_reg_get_empty(void)
{
  const param_reg_t *base = kRegTable;
  const param_reg_t *limit = &kRegTable[kParamCap];

  // find if an empty space then return it.
  for (param_reg_t *thru = (param_reg_t *)base; thru < limit; ++thru)
    if (!strcmp("\0\0\0\0", thru->name))
      return thru;
  // otherwise, return exception.
  return NULL;
}

static void param_eeprom_copy(void)
{
  // traverse eeprom mem
  UINTPTR_T base = (UINTPTR_T)kBase;
  UINTPTR_T limit = (UINTPTR_T)kLimit;
  param_hdr_t *thru = (param_hdr_t *)base; 
  void *src;
  void *dest;
  UINTPTR_T pld_size;

  /*uint8_t i = 0;*/
  while ((UINTPTR_T)thru < limit) {
    /*sleep(1);*/
    /*printf("[%3d]: thru: 0x%08lX\n", ++i, (UINTPTR_T)thru);*/
    // sealed, continue
    if (thru->seal == kSealed && thru->size != kBlankSize) {
      thru = (param_hdr_t *)((UINTPTR_T)thru + thru->size);
    }
    // unsealed & not blank size, register param
    else if (thru->seal != kSealed && thru->size != kBlankSize) {
      pld_size = thru->size - sizeof(param_hdr_t);
      src = (void *)thru + sizeof(param_hdr_t);  // src from EEPROM
      dest = param_reg(thru->name, pld_size);    // dest to RAM
      memcpy(dest, src, pld_size);               //
      thru = (param_hdr_t *)((UINTPTR_T)thru + thru->size);
    }
    // unsealed & blank size, go next block
    else if (thru->seal != kSealed && thru->size == kBlankSize) {
      break;  // not yet
    }
    // exception
    else {
    }

  }
}

static UINTPTR_T *param_cursor_renew(void)
{

}

static UINTPTR_T cksum_cal(UINTPTR_T *arr, UINTPTR_T size)
{
  UINTPTR_T result = UINTPTR_MAX;

  for (UINTPTR_T i = 0; i < size/sizeof(UINTPTR_T); ++i)
    result ^= arr[i];
  return ~result;
}

/**************************************************
 * Test                                           *
 **************************************************/
#if PARAMETER_DEBUG
// print reg table
static void param_print(void)
{
  param_reg_t *thru;

  for (thru = kRegTable; thru < &kRegTable[kParamCap]; ++thru)
    if (strcmp((char *)"\0\0\0\0", thru->name))
      printf("  param_reg_t name: \"%4s\", ptr: 0x%08lX, size: 0x%04lX\n", thru->name, (UINTPTR_T)thru->ptr, ((param_hdr_t *)thru->ptr)->size);
}

static void ram_print(void)
{
  uint64_t *cursor = (uint64_t *)kRam;
  uint8_t *v;

  printf("ram print:\n");
  for (uint16_t i = 0; i < 0x100/8; ++i) {
    v = (uint8_t *)cursor;
    printf(" %02X%02X%02X%02X", v[0], v[1], v[2], v[3]);
    printf(" %02X%02X%02X%02X", v[4], v[5], v[6], v[7]);
    ++cursor;
    if (i % 4 == 3)
      printf("\n");
  }
  printf("\n");
}

static void eeprom_make(void)
{
  param_hdr_t *cursor = (param_hdr_t *)kBase;

  strcpy(cursor->name, "01st");
  cursor->size = 0x40;
  cursor->seal = kSealed;
  memset((void *)cursor + sizeof(param_hdr_t), 0xAA, (cursor->size - sizeof(param_hdr_t)));
  cursor = (param_hdr_t *)((UINTPTR_T)cursor + cursor->size);

  strcpy(cursor->name, "02nd");
  cursor->size = 0x40;
  memset((void *)cursor + sizeof(param_hdr_t), 0xBB, (cursor->size - sizeof(param_hdr_t)));
  cursor = (param_hdr_t *)((UINTPTR_T)cursor + cursor->size);

  strcpy(cursor->name, "01st");
  cursor->size = 0x80;
  memset((void *)cursor + sizeof(param_hdr_t), 0xAA, (cursor->size - sizeof(param_hdr_t)));
}

static void eeprom_print(void)
{
  uint64_t *cursor = (uint64_t *)kEeprom;
  uint8_t *v;

  printf("eeprom print:\n");
  for (uint16_t i = 0; i < 0x100/8; ++i) {
    v = (uint8_t *)cursor;
    printf(" %02X%02X%02X%02X", v[0], v[1], v[2], v[3]);
    printf(" %02X%02X%02X%02X", v[4], v[5], v[6], v[7]);
    ++cursor;
    if (i % 4 == 3)
      printf("\n");
  }
  printf("\n");
}
#endif
