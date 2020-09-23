
/*  -- LAPACK auxiliary routine (version 3.1) --                         */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..    */
/*     November 2006                                                     */
/*                                                                       */
/*     .. Scalar Arguments ..                                            */
/*     ..                                                                */
/*                                                                       */
/*  Purpose                                                              */
/*  =======                                                              */
/*                                                                       */
/*  SLARTG generate a plane rotation so that                             */
/*                                                                       */
/*     [  CS  SN  ]  .  [ F ]  =  [ R ]   where CS**2 + SN**2 = 1.       */
/*     [ -SN  CS  ]     [ G ]     [ 0 ]                                  */
/*                                                                       */
/*  This is a slower, more accurate version of the BLAS1 routine SROTG,  */
/*  with the following other differences:                                */
/*     F and G are unchanged on return.                                  */
/*     If G=0, then CS=1 and SN=0.                                       */
/*     If F=0 and (G .ne. 0), then CS=0 and SN=1 without doing any       */
/*        floating point operations (saves work in SBDSQR when           */
/*        there are zeros on the diagonal).                              */
/*                                                                       */
/*  If F exceeds G in magnitude, CS will be positive.                    */
/*                                                                       */
/*  Arguments                                                            */
/*  =========                                                            */
/*                                                                       */
/*  F       (input) REAL                                                 */
/*          The first component of vector to be rotated.                 */
/*                                                                       */
/*  G       (input) REAL                                                 */
/*          The second component of vector to be rotated.                */
/*                                                                       */
/*  CS      (output) REAL                                                */
/*          The cosine of the rotation.                                  */
/*                                                                       */
/*  SN      (output) REAL                                                */
/*          The sine of the rotation.                                    */
/*                                                                       */
/*  R       (output) REAL                                                */
/*          The nonzero component of the rotated vector.                 */
/*                                                                       */
/*  This version has a few statements commented out for thread safety    */
/*  (machine parameters are computed on each entry). 10 feb 03, SJH.     */
/*                                                                       */
/*  ==================================================================== */

#include "f2c.h"
#include "blaswrap.h"

int slartg_(real *f, real *g, real *cos, real *sin, real *r)
{
    /* Initialized data */
    static logical first = TRUE_;
    
    /* System generated locals */
    real R1, R2;

    /* Builtin functions */
    double log(doublereal), sqrt(doublereal);
    double pow_ri_x(real , integer);

    /* Local variables */
    real f1, g1, r1, eps, scale, makeup;
    integer count;
    static real safmin = 0;
    static real safmin2, safmax2;

    if (*g == 0.f) 
    {
        *cos = 1.f;
        *sin = 0.f;
        *r = *f;
        return 0;
    } 
    else if (*f == 0.f) 
    {
        *cos = 0.f;
        *sin = 1.f;
        *r = *g;
        return 0;
    } 
    
    if(first)
    {
        safmin = slamch_table[PPT_S];
        eps = slamch_table[PPT_E];
        safmin2 = pow_ri_x(slamch_table[PPT_B], (integer) (log((double)(safmin / eps)) / log(slamch_table[PPT_B]) / 2.f));
        safmax2 = 1.f / safmin2;
	first = FALSE_;
    }
    
    f1 = *f;
    g1 = *g;
    R1 = dabs(f1), R2 = dabs(g1);
    scale = dmax(R1,R2);
    if (scale > safmax2) 
    {
        count = 0;
	makeup = 1.f;
        do {
            ++ count;
            f1 *= safmin2;
            g1 *= safmin2;
            R1 = dabs(f1), R2 = dabs(g1);
            scale = dmax(R1,R2);
	    makeup *= safmax2;
        } while(scale > safmax2);

        r1 = SQRT(f1 * f1 + g1 * g1);
        *cos = f1 / r1;
        *sin = g1 / r1;
	*r = r1 * makeup;
    } 
    else if (scale < safmin2) 
    {
        count = 0;
	makeup = 1.f;
        do {
            ++count;
            f1 *= safmax2;
            g1 *= safmax2;
            R1 = dabs(f1), R2 = dabs(g1);
            scale = dmax(R1,R2);
	    makeup *= safmin2;
        } while(scale < safmin2);

        r1 = SQRT(f1 * f1 + g1 * g1);
        *cos = f1 / r1;
        *sin = g1 / r1;
	*r = r1 * makeup;
    } 
    else 
    {
        r1 = SQRT(f1 * f1 + g1 * g1);
        *cos = f1 / r1;
        *sin = g1 / r1;
	*r = r1;
    }
	
    if (dabs(*f) > dabs(*g) && *cos < 0.f) 
    {
        *cos = -(*cos);
        *sin = -(*sin);
        *r = -r1;
    }

    return 0;
}


//======================================================================

int slartg_x(real f1, real g1, real *cos, real *sin, real *r)
{
    /* Initialized data */
    static logical first = TRUE_;
    
    /* System generated locals */
    real R1, R2;

    /* Builtin functions */
    double log(doublereal), sqrt(doublereal);
    double pow_ri_x(real , integer);

    /* Local variables */
    real r1, eps, scale, makeup;
    integer count;
    static real safmin = 0;
    static real safmin2, safmax2;

    if (g1 == 0.f) 
    {
        *cos = 1.f;
        *sin = 0.f;
        *r = f1;
        return 0;
    } 
    else if (f1 == 0.f) 
    {
        *cos = 0.f;
        *sin = 1.f;
        *r = g1;
        return 0;
    } 
    
    if(first)
    {
        safmin = slamch_table[PPT_S];
        eps = slamch_table[PPT_E];
        safmin2 = pow_ri_x(slamch_table[PPT_B], (integer) (log((double)(safmin / eps)) / log(slamch_table[PPT_B]) / 2.f));
        safmax2 = 1.f / safmin2;
	first = FALSE_;
    }
    
    //f1 = *f;
    //g1 = *g;
    R1 = dabs(f1), R2 = dabs(g1);
    scale = dmax(R1, R2);
    if (scale > safmax2) 
    {
        count = 0;
	makeup = 1.f;
        do {
            ++ count;
            f1 *= safmin2;
            g1 *= safmin2;
            R1 = dabs(f1), R2 = dabs(g1);
            scale = dmax(R1,R2);
	    makeup *= safmax2;
        } while(scale > safmax2);

        r1 = SQRT(f1 * f1 + g1 * g1);
        *cos = f1 / r1;
        *sin = g1 / r1;
	*r = r1 * makeup;
    } 
    else if (scale < safmin2) 
    {
        count = 0;
	makeup = 1.f;
        do {
            ++count;
            f1 *= safmax2;
            g1 *= safmax2;
            R1 = dabs(f1), R2 = dabs(g1);
            scale = dmax(R1,R2);
	    makeup *= safmin2;
        } while(scale < safmin2);

        r1 = SQRT(f1 * f1 + g1 * g1);
        *cos = f1 / r1;
        *sin = g1 / r1;
	*r = r1 * makeup;
    } 
    else 
    {
        r1 = SQRT(f1 * f1 + g1 * g1);
        *cos = f1 / r1;
        *sin = g1 / r1;
	*r = r1;
    }
	
    if (dabs(f1) > dabs(g1) && *cos < 0.f) 
    {
        *cos = -(*cos);
        *sin = -(*sin);
        *r = -r1;
    }

    return 0;
}
