
/*  -- LAPACK auxiliary routine (version 3.1) --                         */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd..    */
/*     November 2006                                                     */
/*                                                                       */
/*     .. Scalar Arguments ..                                            */
/*     ..                                                                */
/*     .. Array Arguments ..                                             */
/*     ..                                                                */
/*                                                                       */
/*  Purpose                                                              */
/*  =======                                                              */
/*                                                                       */
/*  CLASR applies a sequence of real plane rotations to a complex matrix */
/*  A, from either the left or the right.                                */
/*                                                                       */
/*  When SIDE = 'L', the transformation takes the form                   */
/*                                                                       */
/*     A := P*A                                                          */
/*                                                                       */
/*  and when SIDE = 'R', the transformation takes the form               */
/*                                                                       */
/*     A := A*P**T                                                       */
/*                                                                       */
/*  where P is an orthogonal matrix consisting of a sequence of z plane  */
/*  rotations, with z = M when SIDE = 'L' and z = N when SIDE = 'R',     */
/*  and P**T is the transpose of P.                                      */
/*                                                                       */
/*  When DIRECT = 'F' (Forward sequence), then                           */
/*                                                                       */
/*     P = P(z-1) * ... * P(2) * P(1)                                    */
/*                                                                       */
/*  and when DIRECT = 'B' (Backward sequence), then                      */
/*                                                                       */
/*     P = P(1) * P(2) * ... * P(z-1)                                    */
/*                                                                       */
/*  where P(k) is a plane rotation matrix defined by the 2-by-2 rotation */
/*                                                                       */
/*     R(k) = (  c(k)  s(k) )                                            */
/*          = ( -s(k)  c(k) ).                                           */
/*                                                                       */
/*  When PIVOT = 'V' (Variable pivot), the rotation is performed         */
/*  for the plane (k,k+1), i.e., P(k) has the form                       */
/*                                                                       */
/*     P(k) = (  1                                            )          */
/*            (       ...                                     )          */
/*            (              1                                )          */
/*            (                   c(k)  s(k)                  )          */
/*            (                  -s(k)  c(k)                  )          */
/*            (                                1              )          */
/*            (                                     ...       )          */
/*            (                                            1  )          */
/*                                                                       */
/*  where R(k) appears as a rank-2 modification to the identity matrix   */
/*  in rows and columns k and k+1.                                       */
/*                                                                       */
/*  When PIVOT = 'T' (Top pivot), the rotation is performed for the      */
/*  plane (1,k+1), so P(k) has the form                                  */
/*                                                                       */
/*     P(k) = (  c(k)                    s(k)                 )          */
/*            (         1                                     )          */
/*            (              ...                              )          */
/*            (                     1                         )          */
/*            ( -s(k)                    c(k)                 )          */
/*            (                                 1             )          */
/*            (                                      ...      )          */
/*            (                                             1 )          */
/*                                                                       */
/*  where R(k) appears in rows and columns 1 and k+1.                    */
/*                                                                       */
/*  Similarly, when PIVOT = 'B' (Bottom pivot), the rotation is          */
/*  performed for the plane (k,z), giving P(k) the form                  */
/*                                                                       */
/*     P(k) = ( 1                                             )          */
/*            (      ...                                      )          */
/*            (             1                                 )          */
/*            (                  c(k)                    s(k) )          */
/*            (                         1                     )          */
/*            (                              ...              )          */
/*            (                                     1         )          */
/*            (                 -s(k)                    c(k) )          */
/*                                                                       */
/*  where R(k) appears in rows and columns k and z.  The rotations are   */
/*  performed without ever forming P(k) explicitly.                      */
/*                                                                       */
/*  Arguments                                                            */
/*  =========                                                            */
/*                                                                       */
/*  SIDE    (input) CHARACTER*1                                          */
/*          Specifies whether the plane rotation matrix P is applied to  */
/*          A on the left or the right.                                  */
/*          = 'L':  Left, compute A := P*A                               */
/*          = 'R':  Right, compute A:= A*P**T                            */
/*                                                                       */
/*  PIVOT   (input) CHARACTER*1                                          */
/*          Specifies the plane for which P(k) is a plane rotation       */
/*          matrix.                                                      */
/*          = 'V':  Variable pivot, the plane (k,k+1)                    */
/*          = 'T':  Top pivot, the plane (1,k+1)                         */
/*          = 'B':  Bottom pivot, the plane (k,z)                        */
/*                                                                       */
/*  DIRECT  (input) CHARACTER*1                                          */
/*          Specifies whether P is a forward or backward sequence of     */
/*          plane rotations.                                             */
/*          = 'F':  Forward, P = P(z-1)*...*P(2)*P(1)                    */
/*          = 'B':  Backward, P = P(1)*P(2)*...*P(z-1)                   */
/*                                                                       */
/*  M       (input) INTEGER                                              */
/*          The number of rows of the matrix A.  If m <= 1, an immediate */
/*          return is effected.                                          */
/*                                                                       */
/*  N       (input) INTEGER                                              */
/*          The number of columns of the matrix A.  If n <= 1, an        */
/*          immediate return is effected.                                */
/*                                                                       */
/*  C       (input) REAL array, dimension                                */
/*                  (M-1) if SIDE = 'L'                                  */
/*                  (N-1) if SIDE = 'R'                                  */
/*          The cosines c(k) of the plane rotations.                     */
/*                                                                       */
/*  S       (input) REAL array, dimension                                */
/*                  (M-1) if SIDE = 'L'                                  */
/*                  (N-1) if SIDE = 'R'                                  */
/*          The sines s(k) of the plane rotations.                       */
/*                                                                       */
/*          The 2-by-2 plane rotation part of the matrix P(k), R(k), has */
/*          the form                                                     */
/*                  R(k) = (  c(k)  s(k) )                               */
/*                         ( -s(k)  c(k) ).                              */
/*                                                                       */
/*  A       (input/output) COMPLEX array, dimension (LDA,N)              */
/*          The M-by-N matrix A.  On exit, A is overwritten by P*A if    */
/*          SIDE = 'R' or by A*P**T if SIDE = 'L'.                       */
/*                                                                       */
/*  LDA     (input) INTEGER                                              */
/*          The leading dimension of the array A.  LDA >= max(1,M).      */
/*                                                                       */
/*  ==================================================================== */

#include <stdio.h>
#include "f2c.h"
#include "blaswrap.h"

//extern int xerbla_(char *, integer *);

#if 0
int clasr_(char *side, char *pivot, char *direct, integer *m, 
	   integer *n, real *cos, real *sin, complex *a, integer *lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, I1, I2, I3, I4;
//    complex Q1, Q2, Q3;
//    complex temp;
//    integer info;

    /* Local variables */
    integer k, j;
    
    real ctemp, stemp;
    real e1r, e1i, e2r, e2i;
    

    /* Parameter adjustments */
    --cos;
    --sin;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */// we just don't check input arguments because of optimization
//    info = 0;
//    if (! (lsame_(side, "L") || lsame_(side, "R"))) {
//	info = 1;
//    } else if (! (lsame_(pivot, "V") || lsame_(pivot, "T") || lsame_(pivot, "B"))) {
//	info = 2;
//    } else if (! (lsame_(direct, "F") || lsame_(direct, "B"))) {
//	info = 3;
//    } else if (*m < 0) {
//	info = 4;
//    } else if (*n < 0) {
//	info = 5;
//    } else if (*lda < max(1,*m)) {
//	info = 9;
//    }
//    if (info != 0) {
//	xerbla_("CLASR ", &info);
//	return 0;
//    }
//
//    if (*m == 0 || *n == 0) {
//	return 0;
//    }

    if (lsame_(side, "L")) /*        Form  P * A */
    {
        if (lsame_(pivot, "V")) 
        {
            if (lsame_(direct, "F")) 
            {
            	I1 = *m - 1;
                for (j = 1; j <= I1; ++j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I2 = *n;
                        for (k = 1; k <= I2; ++k) 
                        {
                            I3 = j + k * a_dim1;
                            I4 = I3 + a_dim1;
			    e1r = a[I3].r,  e1i = a[I3].i;
			    e2r = a[I4].r,  e2i = a[I4].i;
			    
			    a[I4].r = ctemp * e2r - stemp * e1r;
			    a[I4].i = ctemp * e2i - stemp * e1i;
			    a[I3].r = stemp * e2r + ctemp * e1r; 
			    a[I3].i = stemp * e2i + ctemp * e1i;
                        }
                    }
                }
            }
            else if (lsame_(direct, "B")) 
            {
                for (j = *m - 1; j >= 1; --j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I1 = *n;
                        for (k = 1; k <= I1; ++k) 
                        {
                            I3 = j + 1 + k * a_dim1;
                            I2 = j + k * a_dim1;
			    e1r = a[I2].r,  e1i = a[I2].i;
			    e2r = a[I3].r,  e2i = a[I3].i;
			    
			    a[I3].r = ctemp * e2r - stemp * e1r;
			    a[I3].i = ctemp * e2i - stemp * e1i;
			    a[I2].r = stemp * e2r + ctemp * e1r;
			    a[I2].i = stemp * e2i + ctemp * e1i;
                        }
                    }
                }
            }
        } 
        else if (lsame_(pivot, "T")) 
        {
            if (lsame_(direct, "F")) 
            {
                I1 = *m;
                for (j = 2; j <= I1; ++j) 
                {
                    ctemp = cos[j - 1];
                    stemp = sin[j - 1];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I2 = *n;
                        for (k = 1; k <= I2; ++k) 
                        {
                            I3 = j + k * a_dim1;
                            temp.r = a[I3].r, temp.i = a[I3].i;
                            I3 = j + k * a_dim1;
                            Q2.r = ctemp * temp.r, Q2.i = ctemp * temp.i;
                            I4 = k * a_dim1 + 1;
                            Q3.r = stemp * a[I4].r, Q3.i = stemp * a[I4].i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                            I3 = k * a_dim1 + 1;
                            Q2.r = stemp * temp.r, Q2.i = stemp * temp.i;
                            I4 = k * a_dim1 + 1;
                            Q3.r = ctemp * a[I4].r, Q3.i = ctemp * a[I4].i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                        }
                    }
                }
            } 
            else if (lsame_(direct, "B")) 
            {
                for (j = *m; j >= 2; --j) 
                {
                    ctemp = cos[j - 1];
                    stemp = sin[j - 1];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I1 = *n;
                        for (k = 1; k <= I1; ++k) 
                        {
                            I2 = j + k * a_dim1;
                            temp.r = a[I2].r, temp.i = a[I2].i;
                            I2 = j + k * a_dim1;
                            Q2.r = ctemp * temp.r, Q2.i = ctemp * temp.i;
                            I3 = k * a_dim1 + 1;
                            Q3.r = stemp * a[I3].r, Q3.i = stemp * a[I3].i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                            I2 = k * a_dim1 + 1;
                            Q2.r = stemp * temp.r, Q2.i = stemp * temp.i;
                            I3 = k * a_dim1 + 1;
                            Q3.r = ctemp * a[I3].r, Q3.i = ctemp * a[I3].i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                        }
                    }
                }
            }
        } 
        else if (lsame_(pivot, "B")) 
        {
            if (lsame_(direct, "F")) 
            {
                I1 = *m - 1;
                for (j = 1; j <= I1; ++j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I2 = *n;
                        for (k = 1; k <= I2; ++k) 
                        {
                            I3 = j + k * a_dim1;
                            temp.r = a[I3].r, temp.i = a[I3].i;
                            I3 = j + k * a_dim1;
                            I4 = *m + k * a_dim1;
                            Q2.r = stemp * a[I4].r, Q2.i = stemp * a[I4].i;
                            Q3.r = ctemp * temp.r, Q3.i = ctemp * temp.i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                            I3 = *m + k * a_dim1;
                            I4 = *m + k * a_dim1;
                            Q2.r = ctemp * a[I4].r, Q2.i = ctemp * a[I4].i;
                            Q3.r = stemp * temp.r, Q3.i = stemp * temp.i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                        }
                    }
                }
            } 
            else if (lsame_(direct, "B")) 
            {
                for (j = *m - 1; j >= 1; --j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I1 = *n;
                        for (k = 1; k <= I1; ++k) 
                        {
                            I2 = j + k * a_dim1;
                            temp.r = a[I2].r, temp.i = a[I2].i;
                            I2 = j + k * a_dim1;
                            I3 = *m + k * a_dim1;
                            Q2.r = stemp * a[I3].r, Q2.i = stemp * a[I3].i;
                            Q3.r = ctemp * temp.r, Q3.i = ctemp * temp.i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                            I2 = *m + k * a_dim1;
                            I3 = *m + k * a_dim1;
                            Q2.r = ctemp * a[I3].r, Q2.i = ctemp * a[I3].i;
                            Q3.r = stemp * temp.r, Q3.i = stemp * temp.i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                        }
                    }
                }
            }
        }
    } 
    else if (lsame_(side, "R")) /*        Form A * P' */
    {
        if (lsame_(pivot, "V")) 
        {
            if (lsame_(direct, "F")) 
            {
                I1 = *n - 1;
                for (j = 1; j <= I1; ++j)
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I2 = *m;
                        for (k = 1; k <= I2; ++k) 
                        {
                            I3 = k + j * a_dim1;
                            I4 = I3 + a_dim1; 
                            e1r = a[I3].r,  e1i = a[I3].i;
                            e2r = a[I4].r,  e2i = a[I4].i;
			    
                            a[I3].r = ctemp * e1r + stemp * e2r;
                            a[I3].i = ctemp * e1i + stemp * e2i;
                            a[I4].r = ctemp * e2r - stemp * e1r;
                            a[I4].i = ctemp * e2i - stemp * e1i;
                        }
                    }
                }
            } 
            else if (lsame_(direct, "B")) 
            {
                for (j = *n - 1; j >= 1; --j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I1 = *m;
                        for (k = 1; k <= I1; ++k) 
                        {
                            I2 = k + j * a_dim1;
                            I3 = I2 + a_dim1;
                            e1r = a[I2].r, e1i = a[I2].i;
                            e2r = a[I3].r, e2i = a[I3].i;
			    
                            a[I2].r = ctemp * e1r + stemp * e2r;
                            a[I2].i = ctemp * e1i + stemp * e2i;
                            a[I3].r = ctemp * e2r - stemp * e1r;
                            a[I3].i = ctemp * e2i - stemp * e1i;
                        }
                    }
                }
            }
        } 
        else if (lsame_(pivot, "T")) 
        {
            if (lsame_(direct, "F")) 
            {
                I1 = *n;
                for (j = 2; j <= I1; ++j) 
                {
                    ctemp = cos[j - 1];
                    stemp = sin[j - 1];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I2 = *m;
                        for (k = 1; k <= I2; ++k) 
                        {
                            I3 = k + j * a_dim1;
                            temp.r = a[I3].r, temp.i = a[I3].i;
                            I3 = k + j * a_dim1;
                            Q2.r = ctemp * temp.r, Q2.i = ctemp * temp.i;
                            I4 = k + a_dim1;
                            Q3.r = stemp * a[I4].r, Q3.i = stemp * a[I4].i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                            I3 = k + a_dim1;
                            Q2.r = stemp * temp.r, Q2.i = stemp * temp.i;
                            I4 = k + a_dim1;
                            Q3.r = ctemp * a[I4].r, Q3.i = ctemp * a[I4].i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                        }
                    }
                }
            } 
            else if (lsame_(direct, "B")) 
            {
                for (j = *n; j >= 2; --j) 
                {
                    ctemp = cos[j - 1];
                    stemp = sin[j - 1];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I1 = *m;
                        for (k = 1; k <= I1; ++k) 
                        {
                            I2 = k + j * a_dim1;
                            temp.r = a[I2].r, temp.i = a[I2].i;
                            I2 = k + j * a_dim1;
                            Q2.r = ctemp * temp.r, Q2.i = ctemp * temp.i;
                            I3 = k + a_dim1;
                            Q3.r = stemp * a[I3].r, Q3.i = stemp * a[I3].i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                            I2 = k + a_dim1;
                            Q2.r = stemp * temp.r, Q2.i = stemp * temp.i;
                            I3 = k + a_dim1;
                            Q3.r = ctemp * a[I3].r, Q3.i = ctemp * a[I3].i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                        }
                    }
                }
            }
        } 
        else if (lsame_(pivot, "B")) 
        {
            if (lsame_(direct, "F")) 
            {
                I1 = *n - 1;
                for (j = 1; j <= I1; ++j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I2 = *m;
                        for (k = 1; k <= I2; ++k) 
                        {
                            I3 = k + j * a_dim1;
                            temp.r = a[I3].r, temp.i = a[I3].i;
                            I3 = k + j * a_dim1;
                            I4 = k + *n * a_dim1;
                            Q2.r = stemp * a[I4].r, Q2.i = stemp * a[I4].i;
                            Q3.r = ctemp * temp.r, Q3.i = ctemp * temp.i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                            I3 = k + *n * a_dim1;
                            I4 = k + *n * a_dim1;
                            Q2.r = ctemp * a[I4].r, Q2.i = ctemp * a[I4].i;
                            Q3.r = stemp * temp.r, Q3.i = stemp * temp.i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I3].r = Q1.r, a[I3].i = Q1.i;
                        }
                    }
                }
            } 
            else if (lsame_(direct, "B")) 
            {
                for (j = *n - 1; j >= 1; --j) 
                {
                    ctemp = cos[j];
                    stemp = sin[j];
                    if (ctemp != 1.f || stemp != 0.f) 
                    {
                        I1 = *m;
                        for (k = 1; k <= I1; ++k) 
                        {
                            I2 = k + j * a_dim1;
                            temp.r = a[I2].r, temp.i = a[I2].i;
                            I2 = k + j * a_dim1;
                            I3 = k + *n * a_dim1;
                            Q2.r = stemp * a[I3].r, Q2.i = stemp * a[I3].i;
                            Q3.r = ctemp * temp.r, Q3.i = ctemp * temp.i;
                            Q1.r = Q2.r + Q3.r, Q1.i = Q2.i + Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                            I2 = k + *n * a_dim1;
                            I3 = k + *n * a_dim1;
                            Q2.r = ctemp * a[I3].r, Q2.i = ctemp * a[I3].i;
                            Q3.r = stemp * temp.r, Q3.i = stemp * temp.i;
                            Q1.r = Q2.r - Q3.r, Q1.i = Q2.i - Q3.i;
                            a[I2].r = Q1.r, a[I2].i = Q1.i;
                        }
                    }
                }
            }
        }
    }

    return 0;
} /* clasr_ */
#endif


int clasr_LVF(integer m, integer n, real *cos, real *sin, complex *a, integer a_dim1)
{
    integer I3, I4, k, j;
    real ctemp, stemp, e1r, e1i, e2r, e2i;
    
    --cos;
    --sin;
    a -= 1 + a_dim1;
    m --;
    
    for (j = 1; j <= m; ++j) 
    {
        ctemp = cos[j];
        stemp = sin[j];
        if (ctemp != 1.f || stemp != 0.f) 
        {
            I3 = j;
            I4 = j + a_dim1;
            for (k = 1; k <= n; ++k) 
            {
                I3 += a_dim1;
                I4 += a_dim1;
                e1r = a[I3].r,  e1i = a[I3].i;
                e2r = a[I4].r,  e2i = a[I4].i;
			    
                a[I4].r = ctemp * e2r - stemp * e1r;
                a[I4].i = ctemp * e2i - stemp * e1i;
                a[I3].r = stemp * e2r + ctemp * e1r; 
                a[I3].i = stemp * e2i + ctemp * e1i;
            }
        }
    }
    return 0;
} 

int clasr_LVB(integer m, integer n, real *cos, real *sin, complex *a, integer a_dim1)
{
    integer I2, I3, k, j;
    real ctemp, stemp, e1r, e1i, e2r, e2i;
    
    --cos;
    --sin;
    a -= 1 + a_dim1;

    for (j = m - 1; j >= 1; --j) 
    {
        ctemp = cos[j];
        stemp = sin[j];
        if (ctemp != 1.f || stemp != 0.f) 
        {
            I3 = j + 1;
            I2 = j;
            for (k = 1; k <= n; ++k) 
            {
                I3 += a_dim1;
                I2 += a_dim1;
                e1r = a[I2].r,  e1i = a[I2].i;
                e2r = a[I3].r,  e2i = a[I3].i;
			    
                a[I3].r = ctemp * e2r - stemp * e1r;
                a[I3].i = ctemp * e2i - stemp * e1i;
                a[I2].r = stemp * e2r + ctemp * e1r;
                a[I2].i = stemp * e2i + ctemp * e1i;
            }
        }
    }   
    return 0;
} 


int clasr_RVF(integer m, integer n, real *cos, real *sin, complex *a, integer a_dim1)
{
    integer I3, I4, k, j;
    real ctemp, stemp, e1r, e1i, e2r, e2i;
    
    --cos;
    --sin;
    a -= 1 + a_dim1;
    n --;
    
    for (j = 1; j <= n; ++j)
    {
        ctemp = cos[j];
        stemp = sin[j];
        if (ctemp != 1.f || stemp != 0.f) 
        {
            I3 = j * a_dim1;
            I4 = (j+1) * a_dim1;
            for (k = 1; k <= m; ++k) 
            {
                I3 ++;
                I4 ++; 
                e1r = a[I3].r,  e1i = a[I3].i;
                e2r = a[I4].r,  e2i = a[I4].i;
			    
                a[I3].r = ctemp * e1r + stemp * e2r;
                a[I3].i = ctemp * e1i + stemp * e2i;
                a[I4].r = ctemp * e2r - stemp * e1r;
                a[I4].i = ctemp * e2i - stemp * e1i;
            }
        }
    }

    return 0;
} 

int clasr_RVB(integer m, integer n, real *cos, real *sin, complex *a, integer a_dim1)
{
    integer I2, I3, k, j;
    real ctemp, stemp, e1r, e1i, e2r, e2i;
    
    --cos;
    --sin;
    a -= 1 + a_dim1;

    for (j = n - 1; j >= 1; --j) 
    {
        ctemp = cos[j];
        stemp = sin[j];
        if (ctemp != 1.f || stemp != 0.f) 
        {
            I2 = j * a_dim1;
            I3 = I2 + a_dim1;
            for (k = 1; k <= m; ++k) 
            {
                I2 ++;
                I3 ++;
                e1r = a[I2].r, e1i = a[I2].i;
                e2r = a[I3].r, e2i = a[I3].i;
			    
                a[I2].r = ctemp * e1r + stemp * e2r;
                a[I2].i = ctemp * e1i + stemp * e2i;
                a[I3].r = ctemp * e2r - stemp * e1r;
                a[I3].i = ctemp * e2i - stemp * e1i;
            }
        }
    }
    return 0;
} 
