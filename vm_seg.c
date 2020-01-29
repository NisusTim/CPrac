#include <stdbool.h>  // bool
#include <string.h>   // memset(), NULL
#include "vm_seg.h"
#include <stdio.h>

/************************************************
 * Forward Declarations                         *
 ************************************************/
void InitVmSeg(VmSeg *self, void *base, UINTPTR_T size);
/*static void *MAlloc(VmSeg *self, UINTPTR_T size);*/
static void *MAlloc(VmSeg *self, UINTPTR_T size, void **ptr);
static void *CAlloc(VmSeg *self, UINTPTR_T num, UINTPTR_T size);
static void *ReAlloc(VmSeg *self, void *ptr, UINTPTR_T size);
static void Free(VmSeg *self, void *ptr);
static void compaction(mem_priv_t *);
static mem_t *mem_search_allocated(mem_priv_t *, void *);
static inline void mem_table_reset(mem_t *, UINTPTR_T);
static mem_t *mem_blank_get(mem_t *);
#if VM_SEG_DEBUG
void mem_table_dump(mem_t *);
void mem_chain_dump(mem_t *);
void mem_priv_dump(mem_priv_t *);
#endif

/*
int main(void)
{
  VmSeg s;
  uint8_t blank[0x100];

  InitVmSeg(&s, (void *)blank, sizeof(blank));
  void *a, *b, *c, *d;
  s.MAlloc(&s, 0x20, &a);
  s.MAlloc(&s, 0x40, &b);
  s.MAlloc(&s, 0x60, &c);
  s.MAlloc(&s, 0x40, &d);
  mem_chain_dump(s.mem_priv.head);

  printf("### free ###\n");
  s.Free(&s, a);
  s.Free(&s, d);
  mem_chain_dump(s.mem_priv.head);

  printf("### alloc ###\n");
  s.MAlloc(&s, 0x30, &a);
  s.MAlloc(&s, 0x30, &d);
  mem_chain_dump(s.mem_priv.head);
}
*/

/************************************************
 * APIs                                         *
 ************************************************/
void InitVmSeg(VmSeg *self, void *rgn_ptr, UINTPTR_T rgn_size)
{
  /*self->mem_priv.rgn_base = (UINTPTR_T)rgn_ptr;*/
  self->mem_priv.rgn_base = (size_t)rgn_ptr;
  self->mem_priv.rgn_limit = self->mem_priv.rgn_base + rgn_size;
  self->mem_priv.rgn_free = rgn_size;
  self->mem_priv.mem_csize = 0;
  self->mem_priv.head = NULL;
  mem_table_reset(self->mem_priv.mem_table, sizeof(self->mem_priv.mem_table));
  self->MAlloc = MAlloc;
  self->CAlloc = CAlloc;
  self->ReAlloc = ReAlloc;
  self->Free = Free;
}

/************************************************
 * Private Methods                              *
 ************************************************/
static void *MAlloc(VmSeg *self, UINTPTR_T size, void **ptr)
{
  mem_priv_t *priv = &self->mem_priv;

  // insufficient space
  if (size > priv->rgn_free)
    return NULL;

  // case of head
  if (NULL == priv->head) {
    priv->head = &priv->mem_table[0];

    priv->head->base = 0;
    priv->head->size = size;
    priv->head->next = NULL;
    priv->head->reg_ptr = (UINTPTR_T)ptr;

    priv->rgn_free -= size;
    priv->mem_csize += 1;
    return *ptr = (UINTPTR_T *)(priv->rgn_base + priv->head->base);
  } 

  UINTPTR_T space;
  for (mem_t *thru = priv->head; thru != NULL; thru = thru->next) {
    if (NULL != thru->next) {
      space = thru->next->base - (thru->base + thru->size);
    } else {
      space = (priv->rgn_limit - priv->rgn_base) - (thru->base + thru->size);
    }
    if (size <= space) {
      mem_t *blank = mem_blank_get(priv->mem_table);
      // memory table full
      if (NULL == blank)
        return NULL;

      blank->base = thru->base + thru->size;
      blank->size = size;
      blank->next = thru->next;
      blank->reg_ptr = (UINTPTR_T)ptr;

      thru->next = blank;
      priv->rgn_free -= size;
      priv->mem_csize += 1;
      return *ptr = (UINTPTR_T *)(priv->rgn_base + blank->base);
    }
  }

  // fragmentation needs compaction
  compaction(priv);
  return self->MAlloc(self, size, ptr);
}

static void *CAlloc(VmSeg *self, UINTPTR_T num, UINTPTR_T size)
{
}

static void *ReAlloc(VmSeg *self, void *ptr, UINTPTR_T size)
{
}

// unregistered from table.
static void Free(VmSeg *self, void *ptr)
{
  mem_priv_t *priv = &self->mem_priv;

  for (mem_t **thru = &priv->head; *thru != NULL; thru = &(*thru)->next) {
    // found
    if ((UINTPTR_T)ptr == (*thru)->base + priv->rgn_base) {
      mem_t *temp = *thru;

      priv->mem_csize -= 1;
      priv->rgn_free += (*thru)->size;
      (*thru)->base = 0;
      (*thru)->size = 0;
      *(UINTPTR_T **)(*thru)->reg_ptr = NULL;

      *thru = temp->next;
      temp->next = NULL;
      break;
    }
    // end of chain
    if (*thru == NULL)
      break;
  }
}

static void compaction(mem_priv_t *priv)
{
  UINTPTR_T compact = 0;
  UINTPTR_T dest = priv->rgn_base;
  UINTPTR_T src;
  UINTPTR_T size;

  for (mem_t *thru = priv->head; thru != NULL; thru = thru->next) {
    if (compact != thru->base) {
      src = thru->base + priv->rgn_base;
      size = thru->size;
      // memcpy on memory allocated
      memcpy((void *)dest, (const void *)src, size);
      thru->base = compact;
    }
    compact += thru->size;
    dest += thru->size;
  }
}

static inline void mem_table_reset(mem_t *table, UINTPTR_T table_size)
{
  memset(table, 0, table_size);
}

static mem_t *mem_blank_get(mem_t *table)
{
  for (uint8_t i = 0; i < kMemCap; ++i)
    if (0 == table[i].size && NULL == table[i].next)
      return &table[i];
  return NULL;
}

static mem_t *mem_search_allocated(mem_priv_t *priv, void *ptr)
{
  for (mem_t *thru = priv->head; thru != NULL; thru = thru->next)
    if ((UINTPTR_T)ptr == thru->base + priv->rgn_base)
      return thru;
  return NULL;
}

/**************************************************
 * Test                                           *
 **************************************************/
#if VM_SEG_DEBUG
// dump through array table.
void mem_table_dump(mem_t *table)
{
  for (uint8_t i = 0; i < kMemCap; ++i)
    printf(" [%2u] base: 0x%08lX, size: 0x%08lX, next: 0x%08lX, "\
           "reg_ptr: 0x%08lX\n", 
           i, table[i].base, table[i].size, (UINTPTR_T)table[i].next,
           table[i].reg_ptr);
}

// dump through pointer chain.
void mem_chain_dump(mem_t *thru)
{
  uint8_t i = 0;

  for (; thru != NULL; thru = thru->next)
    printf(" [%2u] base: 0x%08lX, size: 0x%08lX, next: 0x%08lX, " \
           "reg_ptr: 0x%08lX\n", 
           i++, thru->base, thru->size, (UINTPTR_T)thru->next, thru->reg_ptr);
}

// dump priv info.
void mem_priv_dump(mem_priv_t *priv)
{
  printf("  rgn_base:  0x%08lX\n", priv->rgn_base);
  printf("  rgn_limit: 0x%08lX\n", priv->rgn_limit);
  printf("  rgn_total: 0x%08lX\n", priv->rgn_limit - priv->rgn_base);
  printf("  rgn_free:  0x%08lX\n", priv->rgn_free);
  printf("  rgn_used:  0x%08lX\n", priv->rgn_limit - priv->rgn_base - priv->rgn_free);
  printf("  mem_csize:   %8u\n", priv->mem_csize);
}
#endif
