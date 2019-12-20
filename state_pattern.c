#include <stdio.h>
#include <stdlib.h>         // rand(), srand()
#include <time.h>
#include <unistd.h>
#include "state_pattern.h"

void InitCtx(Ctx *);
static void AbsStTransitState(Ctx *ctx, AbsSt *);
static void InitConcStA(Ctx *);
static void InitConcStB(Ctx *);
static void CtxHandle(Ctx *);
static void CtxProcess(Ctx *);
static void CtxTransitState(Ctx *, AbsSt *);
static void ConcStAHandle(Ctx *);
static void ConcStAProcess(Ctx *);
static void ConcStATransitState(Ctx *, AbsSt *);
static void ConcStBHandle(Ctx *);
static void ConcStBProcess(Ctx *);
static void ConcStBTransitState(Ctx *, AbsSt *);

/************************************************
 * Globals                                      *
 ************************************************/
AbsSt state;
uint8_t run = 1;

int main(void)
{
  Ctx inst_c;
  Ctx *c = &inst_c;
  InitCtx(c);
  while (run) {
    c->Handle(c);
    c->Process(c);
  }
}

static void AbsStTransitState(Ctx *ctx, AbsSt *abs_st)
{
  ctx->TransitState(ctx, abs_st);
}

void InitCtx(Ctx *ctx)
{
  srand(time(NULL));
  ctx->s_ = &ctx->state_;
  InitConcStA(ctx);
  ctx->Handle = CtxHandle;
  ctx->Process = CtxProcess;
}

static void CtxHandle(Ctx *ctx)
{
  ctx->s_->Handle(ctx);
}

static void CtxProcess(Ctx *ctx)
{
  ctx->s_->Process(ctx);
}

static void CtxTransitState(Ctx *ctx, AbsSt *state)
{
  ctx->s_ = state;
}

static void InitConcStA(Ctx *ctx)
{
  ctx->s_->Handle = ConcStAHandle;
  ctx->s_->Process = ConcStAProcess;
  ctx->s_->TransitState = AbsStTransitState;
}

static void ConcStAHandle(Ctx *ctx)
{
  /*printf("--State A: Handling...\n");*/
  printf("  Generating a TARGET number between 0-99: ");
  printf("%3u\n", ctx->target = rand() % 100);
  printf("  Generating a OBJECT number between 0-10: ");
  printf("%3u\n", ctx->object = rand() % 11);
  /*printf("--State A: Handling done!\n");*/
}

static void ConcStAProcess(Ctx *ctx)
{
  /*printf("--State A: Processing...\n");*/
  uint8_t die = 1;
    printf("  Rolling a DIE number between 1-6: ");
    printf("%3u\n", die = rand() % 6 + 1);
    if (ctx->target > ctx->object)
      ctx->object += die;
    else
      ctx->object -= die;
    usleep(500000);
    printf("  Now, TARGET: %3u;  OBJECT: %3u;\n", ctx->target, ctx->object);
  /*printf("--State A: Processing done!\n");*/
  ConcStATransitState(ctx, NULL);
}

static void ConcStATransitState(Ctx *ctx, AbsSt *state)
{
  if (ctx->target != ctx->object) {
    ConcStAProcess(ctx);
  }
  else {
    printf("\n");
    printf("SUCCEED!!\n");
    printf("\n");
    InitConcStB(ctx);
    /*ctx->TransitState(ctx, state);*/
  }
}

static void InitConcStB(Ctx *ctx)
{
  ctx->s_->Handle = ConcStBHandle;
  ctx->s_->Process = ConcStBProcess;
}

static void ConcStBHandle(Ctx *ctx)
{
  run = 0;
  printf("--State B: Handling...\n");
  printf("THE END!\n");
  printf("--State B: Handling done!\n");
}

static void ConcStBProcess(Ctx *ctx)
{
}

static void ConcStBTransitState(Ctx *ctx, AbsSt *state)
{
}
