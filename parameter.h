#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "vm_seg.h"

#define PARAMETER_DEBUG   1

void *param_reg(char *name, UINTPTR_T pld_size);
bool param_unreg(char *name);
void param_write(char *name);

#endif  // PARAMETER_H_
