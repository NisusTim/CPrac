// practices and notes extracted from <linux/stddef.h>
#ifndef LINUX_KERNEL_H_
#define LINUX_KERNEL_H_

// container_of(ptr, type, member): cast a member of a structure out of the 
// containing structure
// @ptr: The pointer to the member.
// @type: The type of the container struct this is embedded in.
// @member: The name of the member within the struct.
#define container_of(ptr, type, member) ({  \
  void *__mptr = (void *)(ptr);  \
  ((type *)(__mptr - offsetof(type, member))); })

#endif  /* LINUX_KERNEL_H_ */
