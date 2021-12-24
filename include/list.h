#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_head{
  struct list_head *next, *prev;
} list_head;


// get struct entry from this list_head
#define list_entry(ptr, type, member) ({\
  const typeof( ((type *)0)->member ) *__mptr = (ptr);\
  (type *)( (char *)__mptr - _offsetof(type, member));\
  })

// get offset of a member var
#define _offsetof(type, member) \
  ( (size_t) &((type *)0)->member )

#define LIST_HEAD_INIT(name) {&(name), &(name)}

#define LIST_HEAD(name) \
  struct list_head name = LIST_HEAD_INIT(name)

#define list_for_each(pos, head)\
  for (pos = (head)->next; prefetch(pos->next), pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head)\
  for (pos = (head)->next, n = pos->next; pos != (head);\
      pos = n, n = pos->next)

static inline void INIT_LIST_HEAD(struct list_head *list) {
  list->next = list;
  list->prev = list;
}
static inline void __list_add(struct list_head *new,
                              struct list_head *prev,
                              struct list_head *next) {
  next->prev = new;
  prev->next = new;
  new->prev = prev;
  new->next = next;
}
static inline void list_add(struct list_head *new, struct list_head *head) {
  __list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head) {
  __list_add(new, head->prev, head);
}
static inline void list_del(struct list_head *node) {
  struct list_head *prev = node->prev;
  struct list_head *next = node->next;
  prev->next = next;
  next->prev = prev;
}
static inline int list_empty(const struct list_head *head) {
  return head->next == head;
}

#endif
