

#include <stdlib.h>
#include <math.h>
#include "sys_shared.h"
#include "association.h"
#include "coefs.h"
#include "track_data.h"

//#define PI acos(-1.0)
// 1. angle dec while range inc
// 2. get angle from target_point in target.h

// API
void API_NewMeasAsn(MeasAsn *self);
static meta_meas_group_t *API_Association(MeasAsn *self, target_group_t *, float);
// Method
static void InitMeasAsn(MeasAsn *self);
static void RegisterAlgMinXY(MeasAsn *self);
static void InitAssociation(MeasAsn *self);
static void Pairing(MeasAsn *self, meta_meas_t *,meta_meas_group_t *);
static int8_t PairingExpVel(MeasAsn *self, meta_meas_t *, meta_meas_t *, float*);
static meta_meas_t CalDeltaByMinXY(MeasAsn *self, meta_meas_t *, meta_meas_t *,
  int8_t, int8_t);
static meta_meas_t CalGateByMinXY(MeasAsn *self, meta_meas_t *, meta_meas_t *);
static int8_t IsGatePassedByMinXY(MeasAsn *self, meta_meas_t *, meta_meas_t *,
  float *);

/**************************************************
 * Globals                                        *
 **************************************************/
static meta_meas_t (*CalDelta)(MeasAsn *self, meta_meas_t *, meta_meas_t *, 
  int8_t, int8_t);
static meta_meas_t (*CalGate)(MeasAsn *self, meta_meas_t *, meta_meas_t *);
static int8_t (*IsGatePassed)(MeasAsn *self, meta_meas_t *, meta_meas_t *,
  float *);

/**************************************************
 * API                                            *
 **************************************************/
void API_NewMeasAsn(MeasAsn *self)
{
  self->curr_idx = META_MEAS_GROUP_CAP - 1;
  self->API_Association = API_Association;
  self->curr = &self->mmgs[self->curr_idx];
  self->prev = &self->mmgs[self->curr_idx - 1];
  // register algorithm
  InitMeasAsn(self);
}

static meta_meas_group_t *API_Association(MeasAsn *self, target_group_t *tgg, float dt)
{
  InitAssociation(self);

  meta_meas_group_t *curr = self->curr;
  meta_meas_t *mm=curr->mm;
  target_t *tg=tgg->targets,*tg_end=tgg->targets+tgg->tcnt;

  curr->tgg = tgg;
  curr->vel_max = tgg->vbins * tgg->vunit;

  while(tg < tg_end){
	if (tg->aoaidx == AOAIDX_INVALID){
		tg++;
		continue;
	}

	mm->tg = tg;
	mm->aoaidx = tg->aoaidx;
	mm->range = tg->range * tgg->runit;
	mm->rng_x = mm->range * aoaidx_sin(tg->aoaidx);
	mm->rng_y = mm->range * aoaidx_cos(tg->aoaidx);
	mm->vel = tg->velocity * tgg->vunit;
	mm++;
	tg++;
  }

  self->time_delta = dt;
  curr->mm_cnt = mm-curr->mm;
  for(meta_meas_t* m = curr->mm; m < mm; m++)
	Pairing(self, m, self->prev);

  return self->curr;
}

/**************************************************
 * Methods                                        *
 **************************************************/
static void InitMeasAsn(MeasAsn *self)
{
  RegisterAlgMinXY(self);  // default algorithm: MinXY
}

static void RegisterAlgMinXY(MeasAsn *self)
{
  CalDelta = CalDeltaByMinXY;
  CalGate = CalGateByMinXY;
  IsGatePassed = IsGatePassedByMinXY;
}

static void InitAssociation(MeasAsn *self)
{
  // update curr and prev
  self->curr_idx = (self->curr_idx + 1) % META_MEAS_GROUP_CAP;
  self->prev = self->curr;
  self->curr = &self->mmgs[self->curr_idx];

  // init curr flip
  for (uint16_t thru = 0; thru < self->curr->mm_cnt; ++thru) {
    self->curr->mm[thru].flip = kNotPaired;
  }
}

static void Pairing(MeasAsn *self, meta_meas_t *curr_mm, meta_meas_group_t* past_mmg)
{
  float delta_rng = MAX_VELOCITY_SUPPORTED*self->time_delta;
  float token = 10000.0;
  int8_t flip;
  ASSO_DEBUG("Cu[%.1f,%.2f,%.1f]\n",curr_mm->range, aoaidx_asin(curr_mm->aoaidx), curr_mm->vel);
  for (meta_meas_t *prev_mm = past_mmg->mm; prev_mm < (past_mmg->mm+past_mmg->mm_cnt); prev_mm++) {
    if ((curr_mm->range+delta_rng) < prev_mm->range)  // next curr_mm
    	break;

    if (curr_mm->range <= (prev_mm->range+delta_rng)){ // next prev_mm
        ASSO_DEBUG("Pv[%.1f,%.2f,%.1f]\n",prev_mm->range, aoaidx_asin(prev_mm->aoaidx), prev_mm->vel);
    	flip = PairingExpVel(self, curr_mm, prev_mm, &token);
    	if(flip != kNotPaired)
    		curr_mm->flip = flip;
    }
  }
}

static int8_t PairingExpVel(
  MeasAsn *self, meta_meas_t *curr_mm, meta_meas_t *prev_mm, float* token)
{
  int8_t flip = kNotPaired;
  for (int8_t curr_mult_vel = -self->mult_vel; curr_mult_vel < self->mult_vel + 1;
       ++curr_mult_vel) {
    // thru current multiples of vel
    int8_t prev_mult_vel;
    int8_t prev_mult_vel_end;
    if (prev_mm->flip != kNotPaired) {  // if paired, no iteration
      prev_mult_vel = prev_mm->flip;
      prev_mult_vel_end = prev_mult_vel;  
    } else {
      prev_mult_vel = -self->mult_vel;
      prev_mult_vel_end = self->mult_vel;
    }

    for (; prev_mult_vel < prev_mult_vel_end + 1; ++prev_mult_vel) {
      // thru previous multiples of vel
      meta_meas_t gate = CalGate(self, curr_mm, prev_mm);
      meta_meas_t delta = CalDelta(self, curr_mm, prev_mm, 
                                   curr_mult_vel, prev_mult_vel);

      ASSO_DEBUG("F[%d,%d],D[%.1f,%.1f,%.1f]\n",curr_mult_vel,
  			prev_mult_vel, delta.rng_x, delta.rng_y, delta.vel);
      if (IsGatePassed(self, &gate, &delta, token)) {
        flip = curr_mult_vel;
        // to update vel of curr_mm
        // curr_mm->vel = ExpVel(curr_mm->vel, self->curr->vel_max, flip);
        // return flip;
      }
    }
  }
  return flip;
}

static meta_meas_t CalGateByMinXY(
  MeasAsn *self, meta_meas_t *curr_mm, meta_meas_t *prev_mm)
{
  return self->gate;
}

static meta_meas_t CalDeltaByMinXY(
  MeasAsn *self, meta_meas_t *curr_mm, meta_meas_t *prev_mm, int8_t curr_mult,
  int8_t prev_mult)
{
  const float dt = self->time_delta;  // second
  const float curr_v_max = self->curr->vel_max;
  const float prev_v_max = self->prev->vel_max;
  const float vel_y = EXP_VEL(prev_mm->vel, prev_v_max, prev_mult)/aoaidx_cos(prev_mm->aoaidx);
  meta_meas_t delta = {0};

  delta.rng_x = DELTA(curr_mm->rng_x,prev_mm->rng_x);
  delta.rng_y = DELTA(curr_mm->rng_y,(prev_mm->rng_y + vel_y * dt));
  delta.vel = DELTA(EXP_VEL(curr_mm->vel, curr_v_max, curr_mult),EXP_VEL(prev_mm->vel, prev_v_max, prev_mult));

  return delta;
}

static int8_t IsGatePassedByMinXY(
  MeasAsn *self, meta_meas_t *gate, meta_meas_t *delta, float *token)
{
  if (gate->rng_x >= delta->rng_x && gate->rng_y >= delta->rng_y && gate->vel >= delta->vel) {
	float rr = delta->rng_x*delta->rng_x + delta->rng_y*delta->rng_y;
	if(rr < *token){
		*token = rr;
		return 1;
	}
  }
  return 0;
}
