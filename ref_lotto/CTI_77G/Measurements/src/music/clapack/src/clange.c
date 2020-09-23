#include "f2c.h"
#include "blaswrap.h"

/* Table of constant values */

static integer c__1 = 1;
    double c_abs(complex *), sqrt(doublereal);
    extern int classq_(integer *, complex *, integer *, real *, real *);

doublereal clange_(char *norm, integer *m, integer *n, complex *a, integer *lda, real *work)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    real ret_val, r__1, r__2;

    /* Local variables */
    integer i__, j;
    real sum, scale;
    real value;
    complex *c;


/*  -- LAPACK auxiliary routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CLANGE  returns the value of the one norm,  or the Frobenius norm, or */
/*  the  infinity norm,  or the  element of  largest absolute value  of a */
/*  complex matrix A. */

/*  Description */
/*  =========== */

/*  CLANGE returns the value */

/*     CLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm' */
/*              ( */
/*              ( norm1(A),         NORM = '1', 'O' or 'o' */
/*              ( */
/*              ( normI(A),         NORM = 'I' or 'i' */
/*              ( */
/*              ( normF(A),         NORM = 'F', 'f', 'E' or 'e' */

/*  where  norm1  denotes the  one norm of a matrix (maximum column sum), */
/*  normI  denotes the  infinity norm  of a matrix  (maximum row sum) and */
/*  normF  denotes the  Frobenius norm of a matrix (square root of sum of */
/*  squares).  Note that  max(abs(A(i,j)))  is not a consistent matrix norm. */

/*  Arguments */
/*  ========= */

/*  NORM    (input) CHARACTER*1 */
/*          Specifies the value to be returned in CLANGE as described */
/*          above. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0.  When M = 0, */
/*          CLANGE is set to zero. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0.  When N = 0, */
/*          CLANGE is set to zero. */

/*  A       (input) COMPLEX array, dimension (LDA,N) */
/*          The m by n matrix A. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(M,1). */

/*  WORK    (workspace) REAL array, dimension (MAX(1,LWORK)), */
/*          where LWORK >= M when NORM = 'I'; otherwise, WORK is not */
/*          referenced. */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --work;
    value = 0.f;

    /* Function Body */
    if (min(*m,*n) == 0) 
    {
//	value = 0.f;
    } 
    else if (lsame_(norm, "M")) 
    {
//	value = 0.f;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		c = &a[i__+j*a_dim1];
		value = dmax(value, SQRT(c->r * c->r + c->i * c->i));
	    }
	}
    } 
    else if (lsame_(norm, "O") || *(unsigned char *)norm == '1') 
    {
//	value = 0.f;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    sum = 0.f;
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) 
	    {
		c = &a[i__+j*a_dim1];
		sum += SQRT(c->r * c->r + c->i * c->i); //c_abs(&a[i__ + j * a_dim1]);
	    }
	    value = dmax(value,sum);
	}
    } 
    else if (lsame_(norm, "I")) 
    {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) 
	{
	    work[i__] = 0.f;
	}
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) 
	{
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) 
	    {
	        c = &a[i__ + j * a_dim1];
		work[i__] += SQRT(c->r * c->r + c->i * c->i);
	    }
	}
	value = 0.f;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) 
	{
	    r__1 = value, r__2 = work[i__];
	    value = dmax(r__1,r__2);
	}
    } 
    else if (lsame_(norm, "F") || lsame_(norm, "E")) 
    {
	scale = 0.f;
	sum = 1.f;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) 
	{
	    classq_(m, &a[j * a_dim1 + 1], &c__1, &scale, &sum);
	}
	value = scale * SQRT(sum);
    }

    ret_val = value;
    return ret_val;
} /* clange_ */
