// practices and notes extracted from <linux/stddef.h>
// ref: http://blog.linux.org.tw/~jserv/archives/001399.html
#ifndef LINUX_STDDEF_H_
#define LINUX_STDDEF_H_

#undef NULL
#define NULL  ((void *)0)

enum {
  false = 0,
  true  = 1
};

// offsetof(TYPE, MEMBER): 
// Highly platform-dependent and not work with bitfields.
// @TYPE: The type of structure
// @MEMBER: The member within structure to get the offset of
#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER)  __compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER)  ((size_t)&((TYPE *)0)->MEMBER)
#endif

// sizeof_field(TYPE, MEMBER):
// @TYPE: The structure containing the field of interest
// @MEMBER: The field to return the size of
#define sizeof_field(TYPE, MEMBER)  sizeof(((TYPE *)0)->MEMBER)
//#define offsetofend(TYPE, MEMBER)  sizeof((((TYPE *)0)->MEMBER)) ??

// offsetofend(TYPE, MEMBER):
// @TYPE: The type of the structure
// @MEMBER: The member within the structure to get the end offset of
#define offsetofend(TYPE, MEMBER)  \
  (offsetof(TYPE, MEMBER) + sizeof_field(TYPE, MEMBER))

#endif  // LINUX_STDDEF_H_
