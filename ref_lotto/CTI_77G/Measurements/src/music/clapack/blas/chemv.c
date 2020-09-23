
/*  Purpose                                                              */
/*  =======                                                              */
/*                                                                       */
/*  CHEMV  performs the matrix-vector  operation                         */
/*                                                                       */
/*     y := alpha*A*x + beta*y,                                          */
/*                                                                       */
/*  where alpha and beta are scalars, x and y are n element vectors and  */
/*  A is an n by n hermitian matrix.                                     */
/*                                                                       */
/*  Arguments                                                            */
/*  ==========                                                           */
/*                                                                       */
/*  UPLO   - CHARACTER*1.                                                */
/*           On entry, UPLO specifies whether the upper or lower         */
/*           triangular part of the array A is to be referenced as       */
/*           follows:                                                    */
/*                                                                       */
/*              UPLO = 'U' or 'u'   Only the upper triangular part of A  */
/*                                  is to be referenced.                 */
/*                                                                       */
/*              UPLO = 'L' or 'l'   Only the lower triangular part of A  */
/*                                  is to be referenced.                 */
/*                                                                       */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  N      - INTEGER.                                                    */
/*           On entry, N specifies the order of the matrix A.            */
/*           N must be at least zero.                                    */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  ALPHA  - COMPLEX         .                                           */
/*           On entry, ALPHA specifies the scalar alpha.                 */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  A      - COMPLEX          array of DIMENSION ( LDA, n ).             */
/*           Before entry with  UPLO = 'U' or 'u', the leading n by n    */
/*           upper triangular part of the array A must contain the upper */
/*           triangular part of the hermitian matrix and the strictly    */
/*           lower triangular part of A is not referenced.               */
/*           Before entry with UPLO = 'L' or 'l', the leading n by n     */
/*           lower triangular part of the array A must contain the lower */
/*           triangular part of the hermitian matrix and the strictly    */
/*           upper triangular part of A is not referenced.               */
/*           Note that the imaginary parts of the diagonal elements need */
/*           not be set and are assumed to be zero.                      */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  LDA    - INTEGER.                                                    */
/*           On entry, LDA specifies the first dimension of A as declared*/
/*           in the calling (sub) program. LDA must be at least          */
/*           max( 1, n ).                                                */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  X      - COMPLEX          array of dimension at least                */
/*           ( 1 + ( n - 1 )*abs( INCX ) ).                              */
/*           Before entry, the incremented array X must contain the n    */
/*           element vector x.                                           */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  INCX   - INTEGER.                                                    */
/*           On entry, INCX specifies the increment for the elements of  */
/*           X. INCX must not be zero.                                   */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  BETA   - COMPLEX         .                                           */
/*           On entry, BETA specifies the scalar beta. When BETA is      */
/*           supplied as zero then Y need not be set on input.           */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*  Y      - COMPLEX          array of dimension at least                */
/*           ( 1 + ( n - 1 )*abs( INCY ) ).                              */
/*           Before entry, the incremented array Y must contain the n    */
/*           element vector y. On exit, Y is overwritten by the updated  */
/*           vector y.                                                   */
/*                                                                       */
/*  INCY   - INTEGER.                                                    */
/*           On entry, INCY specifies the increment for the elements of  */
/*           Y. INCY must not be zero.                                   */
/*           Unchanged on exit.                                          */
/*                                                                       */
/*                                                                       */
/*  Level 2 Blas routine.                                                */
/*                                                                       */
/*  -- Written on 22-October-1986.                                       */
/*     Jack Dongarra, Argonne National Lab.                              */
/*     Jeremy Du Croz, Nag Central Office.                               */
/*     Sven Hammarling, Nag Central Office.                              */
/*     Richard Hanson, Sandia National Labs.                             */
/*                                                                       */


#include "f2c.h"
#include "blaswrap.h"

    extern int xerbla_(char *, integer *);

int chemv_(char *uplo, integer *n, complex *alpha, complex *a, integer *lda, 
           complex *x, integer *incx, complex *beta, complex *y, integer *incy)
{
    /* System generated locals */
    integer a_dim1, a_offset;

    /* Local variables */
    integer index, j, jx, jy, kx, ky, info;
    complex temp1, temp2;
    complex *ca, *cx, *cy;

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --x;
    --y;

    /* Function Body */
    info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
        info = 1;
    } else if (*n < 0) {
        info = 2;
    } else if (*lda < max(1,*n)) {
        info = 5;
    } else if (*incx == 0) {
        info = 7;
    } else if (*incy == 0) {
        info = 10;
    }
    
    if (info != 0) {
        xerbla_("CHEMV ", &info);
        return 0;
    }
    if (*n == 0 || (alpha->r == 0.f && alpha->i == 0.f && beta->r == 1.f && beta->i == 0.f)) 
    {
        return 0;
    }

    if (*incx > 0) {
        kx = 1;
    } else {
        kx = 1 - (*n - 1) * *incx;
    }
    if (*incy > 0) {
        ky = 1;
    } else {
        ky = 1 - (*n - 1) * *incy;
    }

/*     Start the operations. In this version the elements of A are */
/*     accessed sequentially with one pass through the triangular part */
/*     of A. */

/*     First form  y := beta*y. */

    if (beta->r != 1.f || beta->i != 0.f) 
    {
        if (*incy == 1) 
        {
            if (beta->r == 0.f && beta->i == 0.f) 
            {
                cy = &y[1];
                for (index = 1; index <= *n; ++index) 
                {
                    cy->r = 0.f;
                    cy->i = 0.f;
                    cy ++;
                }
            } 
            else 
            {
                cy = &y[1];
                for (index = 1; index <= *n; ++index) 
                {
                    cy->r = beta->r * cy->r - beta->i * cy->i;
                    cy->i = beta->r * cy->i - beta->i * cy->r;
                    cy ++;
                }
            }
        } 
        else 
        {
            if (beta->r == 0.f && beta->i == 0.f) 
            {
                cy = &y[ky];
                for (index = 1; index <= *n; ++index) 
                {
                    cy->r = 0.f;
                    cy->i = 0.f;
                    cy += *incy;
                }
            } 
            else 
            {
                cy = &y[ky];
                for (index = 1; index <= *n; ++index) 
                {
                    cy->r = beta->r * cy->r - beta->i * cy->i;
                    cy->i = beta->r * cy->i + beta->i * cy->r;
                    cy += *incy;
                }
            }
        }
    }
    if (alpha->r == 0.f && alpha->i == 0.f) 
    {
        return 0;
    }
    
    if (lsame_(uplo, "U")) 
    {
        if (*incx == 1 && *incy == 1) 
        {
            for (j = 1; j <= *n; ++j) 
            {
                temp1.r = alpha->r * x[j].r - alpha->i * x[j].i; 
                temp1.i = alpha->r * x[j].i + alpha->i * x[j].r;
                temp2.r = 0.f; 
                temp2.i = 0.f;
		ca = &a[j*a_dim1+1];
                cx = &x[1];
                cy = &y[1];
                for (index = 1; index <= j-1; index++) 
                {
                    cy->r = cy->r + temp1.r * ca->r - temp1.i * ca->i;
                    cy->i = cy->i + temp1.r * ca->i + temp1.i * ca->r;
                    temp2.r = temp2.r + ca->r * cx->r + ca->i * cx->i;  // here has combind the conjugated a[i]
                    temp2.i = temp2.i + ca->r * cx->i - ca->i * cx->r;
		    ca ++;
                    cx ++;
                    cy ++;
                }
                cy->r = cy->r + ca->r * temp1.r + alpha->r * temp2.r - alpha->i * temp2.i; 
                cy->i = cy->i + ca->r * temp1.i + alpha->r * temp2.i + alpha->i * temp2.r;
            }
        } 
        else 
        {
            jx = kx;
            jy = ky;
            for (j = 1; j <= *n; ++j) 
            {
                temp1.r = alpha->r * x[jx].r - alpha->i * x[jx].i; 
                temp1.i = alpha->r * x[jx].i + alpha->i * x[jx].r;
                temp2.r = 0.f; 
                temp2.i = 0.f;
		ca = &a[1+j*a_dim1];
		cx = &x[kx];
		cy = &y[ky];
                for (index = 1; index <= j-1; index++) 
                {
                    cy->r = cy->r + temp1.r * ca->r - temp1.i * ca->i; 
		    cy->i = cy->i + temp1.r * ca->i + temp1.i * ca->r;
                    temp2.r = temp2.r + ca->r * cx->r + ca->i * cx->i;  // here we combind conjugated a[i]
                    temp2.i = temp2.i + ca->r * cx->i - ca->i * cx->r;
		    ca ++;
		    cx += *incx;
		    cy += *incy;
                }
                y[jy].r = y[jy].r + ca->r * temp1.r + alpha->r * temp2.r - alpha->i * temp2.i; 
                y[jy].i = y[jy].i + ca->r * temp1.i + alpha->r * temp2.i + alpha->i * temp2.r;
                jx += *incx;
                jy += *incy;
            }
        }
    } 
    else 
    {
        if (*incx == 1 && *incy == 1) 
        {
            for (j = 1; j <= *n; ++j) 
            {
                temp1.r = alpha->r * x[j].r - alpha->i * x[j].i; 
                temp1.i = alpha->r * x[j].i + alpha->i * x[j].r;
                temp2.r = 0.f; 
                temp2.i = 0.f;
		
		ca = &a[j+j*a_dim1];
		cx = &x[j];
		cy = &y[j];
		
                y[j].r = y[j].r + ca->r * temp1.r; 
                y[j].i = y[j].i + ca->r * temp1.i;
		
                for (index = j + 1; index <= *n ; ++index) 
                {
		    ca ++;
		    cx ++;
		    cy ++;
		    
                    cy->r = cy->r + temp1.r * ca->r - temp1.i * ca->i;
                    cy->i = cy->i + temp1.r * ca->i + temp1.i * ca->r;
                    temp2.r = temp2.r + ca->r * cx->r + ca->i * cx->i;    // here we combind conjugated a[i]
                    temp2.i = temp2.i + ca->r * cx->i - ca->i * cx->r;
                }
		
                y[j].r = y[j].r + alpha->r * temp2.r - alpha->i * temp2.i; 
                y[j].i = y[j].i + alpha->r * temp2.i + alpha->i * temp2.r;
            }
        } 
        else 
        {
            jx = kx;
            jy = ky;
            for (j = 1; j <= *n; ++j) 
            {
                temp1.r = alpha->r * x[jx].r - alpha->i * x[jx].i; 
                temp1.i = alpha->r * x[jx].i + alpha->i * x[jx].r;
                temp2.r = 0.f; 
                temp2.i = 0.f;
		ca = &a[j+j*a_dim1];
		cx = &x[jx];
		cy = &y[jy];
                y[jy].r = y[jy].r + ca->r * temp1.r; 
                y[jy].i = y[jy].i + ca->r * temp1.i;
                for (index = j + 1; index <= *n; ++index) 
                {
		    ca ++;
		    cx += *incx;
		    cy += *incy;
                    cy->r = cy->r + temp1.r * ca->r - temp1.i * ca->i; 
                    cy->i = cy->i + temp1.r * ca->i + temp1.i * ca->r;
                    temp2.r = temp2.r + ca->r * cx->r + ca->i * cx->i;     // here we combind conjugated a[i]
                    temp2.i = temp2.i + ca->r * cx->i - ca->i * cx->r;
                }
                y[jy].r = y[jy].r + alpha->r * temp2.r - alpha->i * temp2.i; 
                y[jy].i = y[jy].i + alpha->r * temp2.i + alpha->i * temp2.r;
                jx += *incx;
                jy += *incy;
            }
        }
    }
    return 0;
} /* chemv_ */
