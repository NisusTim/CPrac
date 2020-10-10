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

/*
 * offsetof(type, member)
 *
 * @type: The type of structure.
 * @member: The member within structure to get the offset of.
 *
 * Highly platform-dependent and not work with bitfields.
 */
#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(type, member)  __compiler_offsetof(type, member)
#else
#define offsetof(type, member)  ((size_t)&((type *)0)->member)
#endif

/*
 * sizeof_field(type, member)
 *
 * @type: The structure containing the field of interest.
 * @member: The field to return the size of.
 */
#define sizeof_field(type, member)  sizeof(((type *)0)->member)

/*
 * offsetofend(type, member)
 *
 * @type: The type of the structure.
 * @member: The member within the structure to get the end offset of.
 */
#define offsetofend(type, member)  \
  (offsetof(type, member) + sizeof_field(type, member))


#endif  /* LINUX_STDDEF_H_ */
