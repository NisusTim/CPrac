#ifndef NS_LIST_H_
#define NS_LIST_H_

struct list_head {
  struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name)  { &(name), &(name) }

#define LIST_HEAD(name)  \
  struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
  list->next = list;  /* ignore WRITE_ONCE() */
  list->prev = list;
}

static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next)
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;  /* ignore WRITE_ONCE */
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
  __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
  __list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
  next->prev = prev;
  prev->next = next;  /* ignore WRITE_ONCE */
}

static inline void list_del(struct list_head *entry)
{
  __list_del(entry->prev, entry->next);
  entry->next = (void *)0;  /* ignore LIST_POISON */
  entry->prev = (void *)0;
}

static inline void list_replace(struct list_head *old, struct list_head *new)
{
  new->next = old->next;
  new->next->prev = new;
  new->prev = old->prev;
  new->prev->next = new;
}

static inline void list_replace_init(struct list_head *old,
                                     struct list_head *new)
{
  list_replace(old, new);
  INIT_LIST_HEAD(old);
}

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

static inline void list_del_init(struct list_head *entry)
{
  list_del(entry);
  INIT_LIST_HEAD(entry);
}

static inline void list_move(struct list_head *list, struct list_head *head)
{
  list_del(list);
  list_add(list, head);
}

static inline void list_move_tail(struct list_head *list, struct list_head *head)
{
  list_del(list);
  list_add_tail(list, head);
}

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

static inline int list_is_first(const struct list_head *list,
                                const struct list_head *head)
{
  return list->prev == head;
}

static inline int list_empty(const struct list_head *head)
{
  return head->next == head;  /* ignore READ_ONCE */
}

#endif  /* NS_LIST_H_ */
