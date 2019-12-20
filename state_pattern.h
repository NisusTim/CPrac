#ifndef STATE_PATTERN_H_
#define STATE_PATTERN_H_

#include <stdio.h>
#include <stdint.h>

typedef struct _Context Ctx;
typedef struct _AbstractState AbsSt;

// Abstract class of state pattern
#define ABSTRACT_STATE_PUBLIC_MEMBERS(ctx_type)             \
  void (*Handle)(ctx_type *);                               \
  void (*Process)(ctx_type *);                              \

#define ABSTRACT_STATE_PRIVATE_MEMBERS(ctx_type, st_type)   \
  void (*TransitState)(ctx_type *, st_type *);

//typedef struct _AbstractState {
struct _AbstractState {
  //ABSTRACT_STATE_PUBLIC_MEMBERS(struct _Context);
  //ABSTRACT_STATE_PRIVATE_MEMBERS(struct _Context, struct _AbstractState);
  ABSTRACT_STATE_PUBLIC_MEMBERS(Ctx);
  ABSTRACT_STATE_PRIVATE_MEMBERS(Ctx, AbsSt);
};

// Context
//typedef struct _Context {
struct _Context {
  // publilc:
  uint8_t target;
  uint8_t object;
  void   (*Handle)(struct _Context *);
  void   (*Process)(struct _Context *);
  // private:
  AbsSt  state_;
  AbsSt *s_;
  void   (*TransitState)(struct _Context *, AbsSt *);
};

/*
// Concrete classes of state pattern
typedef struct _ConcreteStateA {
  AbsSt *base;
} ConcStA;

typedef struct _ConcreteStateB {
  AbsSt *base;
} ConcStB;
*/

void InitCtx(Ctx *);

#endif  // STATE_PATTERN_H_
