#ifndef FROM_KERNEL_H_
#define FROM_KERNEL_H_

// stddef.h
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H

#undef NULL
#define NULL  ((void *)0)

enum {
  false   = 0,
  true    = 1
};

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(type, member)	__compiler_offsetof(type, member)
#else
#define offsetof(type, member)	(size_t)&((type *)0)->member
#endif

// sizeof_field(type, member)
// @type: The structure containing the field of interest.
// @member: The field to return the size of.
#define sizeof_field(type, member)  sizeof(((type *)0)->member)

// offsetofend(type, member)
// @type: The type of the structure.
// @member: The field within the structure to get the end of.
#define offsetofend(type, member) \
  (offsetof(type, member) + sizeof_field(type, member))

#endif  // _LINUX_STDDEF_H

#endif  // FROM_KERNEL_H_
