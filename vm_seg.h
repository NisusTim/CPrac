#ifndef VM_SEG_H_
#define VM_SEG_H_

#include <stdint.h>

#if UINTPTR_MAX == 0xFFFF
  #define UINTPTR_T uint16_t
#elif UINTPTR_MAX == 0xFFFFFFFF
  #define UINTPTR_T uint32_t
#elif UINTPTR_MAX == 0xFFFFFFFFFFFFFFFF
  #define UINTPTR_T uint64_t
#endif

enum _VmSegPublicConst {
  kMemCap  =  8
};

typedef struct _MEM {
  UINTPTR_T    base;     // rel. addr.
  UINTPTR_T    size;     // rel. addr.
  struct _MEM *next;
  UINTPTR_T    reg_ptr;  // abs. address of registered pointer
} mem_t;

typedef struct _MEM_PRIVATE {
  UINTPTR_T  rgn_base;   // abs. addr.
  UINTPTR_T  rgn_limit;  // abs. addr.
  // UINTPTR_T  total; = rgn_limit - rgn_base;
  // UINTPTR_T  used; 
  UINTPTR_T  rgn_free;
  uint8_t    mem_csize;  // count size
  mem_t *    head;
  mem_t      mem_table[kMemCap];
} mem_priv_t;

typedef struct _VmSeg {
  mem_priv_t mem_priv;
  //void *     (*MAlloc)(struct _VmSeg *self, UINTPTR_T size);
  void *     (*MAlloc)(struct _VmSeg *self, UINTPTR_T size, void **ptr);
  void *     (*CAlloc)(struct _VmSeg *self, UINTPTR_T num, UINTPTR_T size);
  void *     (*ReAlloc)(struct _VmSeg *self, void *ptr, UINTPTR_T size);
  void       (*Free)(struct _VmSeg *self, void *ptr);
} VmSeg;

void InitVmSeg(VmSeg *self, void *ptr, UINTPTR_T size);

#endif  // VM_SEG_H_
