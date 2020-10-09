#ifndef NS_LIST_H_
#define NS_LIST_H_

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

struct list_head {
  struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name)  { &(name), &(name) }

#define LIST_HEAD(name)  \
  struct list_head name = LIST_HEAD_INIT(name)

/*
 * INIT_LIST_HEAD - initialize a list_head structure.
 * @list: list_head structure to be initialized.
 *
 * Initializes the list_head to point to itself.  If it is a list header,
 * the result is an empty list.
 */
static inline void INIT_LIST_HEAD(struct list_head *list)
{
  list->next = list;  /* ignore WRITE_ONCE() */
  list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;  /* ignore WRITE_ONCE */
}

/*
 * list_add - add a new entry.
 * @new: new entry to be added.
 * @head: list head to add it after.
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 *
 * e.g. [a, b, c] + new at b >>> [a, b, new, c]
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
  __list_add(new, head, head->next);
}

/*
 * list_add_tail - add a new entry.
 * @new: new entry to be added.
 * @head: list head to add it before.
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 *
 * e.g. [a, b, c] + new at b >>> [a, new, b, c]
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
  __list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries.
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head *prev, struct list_head *next)
{
  next->prev = prev;
  prev->next = next;  /* ignore WRITE_ONCE */
}

/*
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 *
 * e.g. [a, b, c] - b >>> [a, c]
 */
static inline void list_del(struct list_head *entry)
{
  __list_del(entry->prev, entry->next);
  entry->next = (void *)0;  /* ignore LIST_POISON */
  entry->prev = (void *)0;
}

/*
 * list_replace - replace old entry by new one.
 * @old: the element to be replaced.
 * @new: the new element to insert.
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace(struct list_head *old, struct list_head *new)
{
  new->next = old->next;
  new->next->prev = new;
  new->prev = old->prev;
  new->prev->next = new;
}

/*
 * list_replace_init - replace old entry by new one and initialize the old one.
 * @old: the element to be replaced.
 * @new: the new element to insert.
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace_init(struct list_head *old,
                                     struct list_head *new)
{
  list_replace(old, new);
  INIT_LIST_HEAD(old);
}

/*
 * list_swap - replace entry1 with entry2 and re-add entry1 at entry2's 
 * position.
 * @entry1: the location to place entry2.
 * @entry2: the location to place entry1.
 */
static inline void list_swap(struct list_head *entry1, 
                             struct list_head *entry2)
{
  struct list_head *pos = entry2->prev;

  list_del(entry2);
  list_replace(entry1, entry2);
  if (pos == entry1)
    pos = entry2;
  list_add(entry1, pos);
}

/*
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void list_del_init(struct list_head *entry)
{
  list_del(entry);
  INIT_LIST_HEAD(entry);
}

/*
 * list_move - delete from one list and add as another's head.
 * @list: the entry to move.
 * @head: the head that will precede our entry.
 *
 * e.g. [a, b, c, d] move b at d >>> [a, c, d, b]
 */
static inline void list_move(struct list_head *list, struct list_head *head)
{
  list_del(list);
  list_add(list, head);
}

/*
 * list_move_tail - delete from one list and add as another's tail.
 * @list: the entry to move.
 * @head: the head that will follow our entry.
 *
 * e.g. [a, b, c, d] move b at d >>> [a, c, b, d]
 */
static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
  list_del(list);
  list_add_tail(list, head);
}

/*
 * list_bulk_move_tail - move a subsection of a list to its tail.
 * @head: the head that will follow our entry.
 * @first: first entry to move.
 * @last: last entry to move, can be the same as first.
 *
 * Move all entries between @first and including @last before @head.
 * All three entries must belong to the same linked list.
 */
static inline void list_bulk_move_tail(struct list_head *head,
                                       struct list_head *first,
                                       struct list_head *last)
{
  first->prev->next = last->next;
  last->next->prev = first->prev;

  head->prev->next = first;
  first->prev = head->prev;

  head->prev = last;
  last->next = head;
}

/*
 * list_is_first - tests whether @list is the first entry in list @head.
 * @list: the entry to test.
 * @head: the head of the list.
 */
static inline int list_is_first(const struct list_head *list,
                                const struct list_head *head)
{
  return list->prev == head;
}

/*
 * list_is_last - tests whether @list is the last entry in list @head.
 */
static inline int list_is_last(const struct list_head *list,
                               const struct list_head *head)
{
  return list->next == head;
}

/*
 * list_empty - tests whether a list is empty.
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
  return head->next == head;  /* ignore READ_ONCE */
}

/*
 * list_rotate_left - rotate the list to the left.
 * @head: the head of the list.
 *
 * Move the first after the last (rotate left).
 * Keep the cyclic order of list (rotate).
 * e.g. [a, b, c] >>> [b, c, a]
 */
static inline void list_rotate_left(struct list_head *head)
{
  struct list_head *first;

  if (!list_empty(head)) {
    first = head->next;
    list_move_tail(first, head);
  }
}

/*
 * list_rotate_to_front() - rotate list to specific item.
 * @list: the desired new front of the list.
 * @head: the head of the list.
 *
 * Rotates list so that @list becomes the new front of the list.
 */
static inline void list_rotate_to_front(struct list_head *list,
                                        struct list_head *head)
{
  /*
   * Deletes the list head from the list denoted by @head and
   * places it as the tail of @list, this effectively rotates the 
   * list so that @list is at the front.
   */
  list_move_tail(head, list);
}

/*
 * list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */
static inline int list_is_singular(const struct list_head *head)
{
  return !list_empty(head) && (head->next == head->prev);
}

static inline void __list_cut_position(struct list_head *list,
                                       struct list_head *head,
                                       struct list_head *entry)
{

}

static inline void list_cut_position(struct list_head *list,
                                     struct list_head *head,
                                     struct list_head *entry)
{

}

#endif  /* NS_LIST_H_ */
