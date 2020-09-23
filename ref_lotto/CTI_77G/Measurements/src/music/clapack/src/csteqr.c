
/*  -- LAPACK routine (version 3.1) --                                   */
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
/*  CSTEQR computes all eigenvalues and, optionally, eigenvectors of a   */
/*  symmetric tridiagonal matrix using the implicit QL or QR method.     */
/*  The eigenvectors of a full or band complex Hermitian matrix can also */
/*  be found if CHETRD or CHPTRD or CHBTRD has been used to reduce this  */
/*  matrix to tridiagonal form.                                          */
/*                                                                       */
/*  Arguments                                                            */
/*  =========                                                            */
/*                                                                       */
/*  COMPZ   (input) CHARACTER*1                                          */
/*          = 'N':  Compute eigenvalues only.                            */
/*          = 'V':  Compute eigenvalues and eigenvectors of the original */
/*                  Hermitian matrix.  On entry, Z must contain the      */
/*                  unitary matrix used to reduce the original matrix    */
/*                  to tridiagonal form.                                 */
/*          = 'I':  Compute eigenvalues and eigenvectors of the          */
/*                  tridiagonal matrix.  Z is initialized to the         */
/*                  identity matrix.                                     */
/*                                                                       */
/*  N       (input) INTEGER                                              */
/*          The order of the matrix.  N >= 0.                            */
/*                                                                       */
/*  D       (input/output) REAL array, dimension (N)                     */
/*          On entry, the diagonal elements of the tridiagonal matrix.   */
/*          On exit, if INFO = 0, the eigenvalues in ascending order.    */
/*                                                                       */
/*  E       (input/output) REAL array, dimension (N-1)                   */
/*          On entry, the (n-1) subdiagonal elements of the tridiagonal  */
/*          matrix.                                                      */
/*          On exit, E has been destroyed.                               */
/*                                                                       */
/*  Z       (input/output) COMPLEX array, dimension (LDZ, N)             */
/*          On entry, if  COMPZ = 'V', then Z contains the unitary       */
/*          matrix used in the reduction to tridiagonal form.            */
/*          On exit, if INFO = 0, then if COMPZ = 'V', Z contains the    */
/*          orthonormal eigenvectors of the original Hermitian matrix,   */
/*          and if COMPZ = 'I', Z contains the orthonormal eigenvectors  */
/*          of the symmetric tridiagonal matrix.                         */
/*          If COMPZ = 'N', then Z is not referenced.                    */
/*                                                                       */
/*  LDZ     (input) INTEGER                                              */
/*          The leading dimension of the array Z.  LDZ >= 1, and if      */
/*          eigenvectors are desired, then  LDZ >= max(1,N).             */
/*                                                                       */
/*  WORK    (workspace) REAL array, dimension (max(1,2*N-2))             */
/*          If COMPZ = 'N', then WORK is not referenced.                 */
/*                                                                       */
/*  INFO    (output) INTEGER                                             */
/*          = 0:  successful exit                                        */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value   */
/*          > 0:  the algorithm has failed to find all the eigenvalues   */
/*                in a total of 30*N iterations; if INFO = i, then i     */
/*                elements of E have not converged to zero; on exit, D   */
/*                and E contain the elements of a symmetric tridiagonal  */
/*                matrix which is unitarily similar to the original      */
/*                matrix.                                                */
/*                                                                       */
/*  ==================================================================== */

#include "f2c.h"
#include "blaswrap.h"

#define _CHANGE_ 1

extern doublereal slanst_(char *, integer *, real *, real *);
extern int slasrt_(char *, integer *, real *, integer *);
extern int slae2_(real *, real *, real *, real *, real *);
//extern int clasr_LVF(integer , integer , real *, real *, complex *, integer );
//extern int clasr_LVB(integer , integer , real *, real *, complex *, integer );
extern int clasr_RVF(integer , integer , real *, real *, complex *, integer );
extern int clasr_RVB(integer , integer , real *, real *, complex *, integer );
extern int cswap_(integer *, complex *, integer *, complex *, integer *);
extern int slaev2_(real *, real *, real *, real *, real *, real *, real *);
extern doublereal slapy2_(real *, real *);
//extern doublereal slamch_(char *);
extern int claset_(char *, integer *, integer *, complex *, complex *, complex *, integer *);
extern int xerbla_(char *, integer *);
extern int slascl_(char *, integer *, integer *, real *, real *, integer *, integer *, real *, integer *, integer *);
//extern int slartg_(real *, real *, real *, real *, real *);
extern int slartg_x(real , real , real *, real *, real *);
double r_sign(real *, real *);

/* Table of constant values */

static complex c_b1 = {0.f,0.f};
static complex c_b2 = {1.f,0.f};
static integer C0 = 0;
static integer C1 = 1;
static integer C2 = 2;
static real c_b41 = 1.f;

int csteqr_(char *compz, integer *n, real *d__, real *e, 
	    complex *z__, integer *ldz, real *work, integer *info)
{
    /* Initialized data */
    static logical first = TRUE_;
    
    /* System generated locals */
    integer z_dim1, z_offset, I1, I2;
    real R1, R2;

    /* Local variables */
    static real safmin=0, safmax, eps, eps2, ssfmax, ssfmin;
    real b, cos, f, g;
    integer i__, j, k, l, m;
    real p, r__, sin;
    integer l1, ii, mm, lm1, mm1, nm1;
    real rt1, rt2;
    integer lsv;
    real tst;
    integer lend, jtot;
    real anorm;
    integer lendm1, lendp1;
    integer iscale;
    integer lendsv;
    integer nmaxit, icompz;

    /* Parameter adjustments */
    --d__;
    --e;
    z_dim1 = *ldz;
    z_offset = 1 + z_dim1;
    z__ -= z_offset;
    --work;

    /* Function Body */
    *info = 0;

    if (lsame_(compz, "N")) 
        icompz = 0;
    else if (lsame_(compz, "V")) 
        icompz = 1;
    else if (lsame_(compz, "I")) 
        icompz = 2;
    else 
        icompz = -1;

    if (icompz < 0) 
        *info = -1;
    else if (*n < 0) 
        *info = -2;
    else if (*ldz < 1 || (icompz > 0 && *ldz < max(1,*n))) 
        *info = -6;

    if (*info != 0) 
    {
        I1 = -(*info);
        xerbla_("CSTEQR", &I1);
        return 0;
    }
    else if (*n == 0)
    { 
        return 0;
    }
    else if (*n == 1) 
    {
        if (icompz == 2) 
        {
            I1 = z_dim1 + 1;
            z__[I1].r = 1.f, z__[I1].i = 0.f;
        }
        return 0;
    }

/*     Determine the unit roundoff and over/underflow thresholds. */

    if(first)
    {
        eps = slamch_table[PPT_E];//slamch_("E");
        R1 = eps;
        eps2 = R1 * R1;
        safmin = slamch_table[PPT_S];//slamch_("S");
        safmax = 1.f / safmin;
        ssfmax = SQRT(safmax) / 3.f;
        ssfmin = SQRT(safmin) / eps2;
        first = FALSE_;
    }

/*     Compute the eigenvalues and eigenvectors of the tridiagonal */
/*     matrix. */

    if (icompz == 2) 
    {
        claset_("Full", n, n, &c_b1, &c_b2, &z__[z_offset], ldz);
    }

    nmaxit = *n * 30;
    jtot = 0;

/*     Determine where the matrix splits and choose QL or QR iteration */
/*     for each block, according to whether top or bottom diagonal */
/*     element is smaller. */

    l1 = 1;
    nm1 = *n - 1;

L10:
    if (l1 > *n) 
    {
        goto L160;
    }
    if (l1 > 1) 
    {
        e[l1 - 1] = 0.f;
    }
    if (l1 <= nm1) 
    {
        I1 = nm1;
        for (m = l1; m <= I1; ++m) 
        {
            tst = (R1 = e[m], dabs(R1));
            if (tst == 0.f) 
            {
                goto L30;
            }
            if (tst <= SQRT((R1 = d__[m], dabs(R1))) * SQRT((R2 = d__[m + 1], dabs(R2))) * eps) 
            {
                e[m] = 0.f;
                goto L30;
            }
        }
    }
    m = *n;

L30:
    l = l1;
    lsv = l;
    lend = m;
    lendsv = lend;
    l1 = m + 1;
    if (lend == l) 
    {
        goto L10;
    }
/*     Scale submatrix in rows and columns L to LEND */
    I1 = lend - l + 1;
    anorm = slanst_("I", &I1, &d__[l], &e[l]);
    iscale = 0;
    if (anorm == 0.f) 
    {
        goto L10;
    }
    if (anorm > ssfmax) 
    {
        iscale = 1;
        I1 = lend - l + 1;
        slascl_("G", &C0, &C0, &anorm, &ssfmax, &I1, &C1, &d__[l], n, info);
        I1 = lend - l;
        slascl_("G", &C0, &C0, &anorm, &ssfmax, &I1, &C1, &e[l], n, info);
    } 
    else if (anorm < ssfmin) 
    {
        iscale = 2;
        I1 = lend - l + 1;
        slascl_("G", &C0, &C0, &anorm, &ssfmin, &I1, &C1, &d__[l], n, info);
        I1 = lend - l;
        slascl_("G", &C0, &C0, &anorm, &ssfmin, &I1, &C1, &e[l], n, info);
    }
/*     Choose between QL and QR iteration */
    if ((R1 = d__[lend], dabs(R1)) < (R2 = d__[l], dabs(R2))) 
    {
        lend = lsv;
        l = lendsv;
    }

    if (lend > l) 
    {
/*        QL Iteration */
/*        Look for small subdiagonal element. */
L40:
        if (l != lend) 
        {
            lendm1 = lend - 1;
            I1 = lendm1;
            for (m = l; m <= I1; ++m) 
            {
/* Computing 2nd power */
                R2 = (R1 = e[m], dabs(R1));
                tst = R2 * R2;
                if (tst <= eps2 * (R1 = d__[m], dabs(R1)) * (R2 = d__[m + 1], dabs(R2)) + safmin) 
                {
                    goto L60;
                }
            }
        }
        m = lend;
L60:
        if (m < lend) 
        {
            e[m] = 0.f;
        }
        p = d__[l];
        if (m == l) 
        {
            goto L80;
        }
/*        If remaining matrix is 2-by-2, use SLAE2 or SLAEV2 */
/*        to compute its eigensystem. */
        if (m == l + 1) 
        {
            if (icompz > 0) 
            {
                slaev2_(&d__[l], &e[l], &d__[l + 1], &rt1, &rt2, &cos, &sin);
                work[l] = cos;
                work[*n - 1 + l] = sin;
                clasr_RVB(*n, C2, &work[l], &work[*n - 1 + l], &z__[l * z_dim1 + 1], *ldz);
            } 
            else 
            {
                slae2_(&d__[l], &e[l], &d__[l + 1], &rt1, &rt2);
            }
            d__[l] = rt1;
            d__[l + 1] = rt2;
            e[l] = 0.f;
            l += 2;
            if (l <= lend) 
            {
                goto L40;
            }
            goto L140;
        }

        if (jtot == nmaxit) 
        {
            goto L140;
        }
        ++jtot;
/*        Form shift. */
        g = (d__[l + 1] - p) / (e[l] * 2.f);
        r__ = slapy2_(&g, &c_b41);
        g = d__[m] - p + e[l] / (g + r_sign(&r__, &g));

        sin = 1.f;
        cos = 1.f;
        p = 0.f;
/*        Inner loop */
        mm1 = m - 1;
        I1 = l;
        for (i__ = mm1; i__ >= I1; --i__) 
        {
            f = sin * e[i__];
            b = cos * e[i__];
            slartg_x(g, f, &cos, &sin, &r__);  //slartg_(&g, &f, &cos, &sin, &r__);
            if (i__ != m - 1) 
            {
                e[i__ + 1] = r__;
            }
            g = d__[i__ + 1] - p;
            r__ = (d__[i__] - g) * sin + cos * 2.f * b;
            p = sin * r__;
            d__[i__ + 1] = g + p;
            g = cos * r__ - b;
/*           If eigenvectors are desired, then save rotations. */
            if (icompz > 0) 
            {
                work[i__] = cos;
                work[*n - 1 + i__] = -sin;
            }
        }
/*        If eigenvectors are desired, then apply saved rotations. */
        if (icompz > 0) 
        {
            mm = m - l + 1;
            clasr_RVB(*n, mm, &work[l], &work[*n - 1 + l], &z__[l * z_dim1 + 1], *ldz);
        }

        d__[l] -= p;
        e[l] = g;
        goto L40;
/*        Eigenvalue found. */
L80:
        d__[l] = p;

        ++l;
        if (l <= lend) 
        {
            goto L40;
        }
        goto L140;
    } 
    else 
    {
/*        QR Iteration */
/*        Look for small superdiagonal element. */
L90:
        if (l != lend) 
        {
            lendp1 = lend + 1;
            I1 = lendp1;
            for (m = l; m >= I1; --m) 
            {
/* Computing 2nd power */
                R2 = (R1 = e[m - 1], dabs(R1));
                tst = R2 * R2;
                if (tst <= eps2 * (R1 = d__[m], dabs(R1)) * (R2 = d__[m - 1], dabs(R2)) + safmin) 
                {
                    goto L110;
                }
            }
        }
        m = lend;
L110:
        if (m > lend) 
        {
            e[m - 1] = 0.f;
        }
        p = d__[l];
        if (m == l) 
        {
            goto L130;
        }
/*        If remaining matrix is 2-by-2, use SLAE2 or SLAEV2 */
/*        to compute its eigensystem. */
        if (m == l - 1) 
        {
            if (icompz > 0) 
            {
                slaev2_(&d__[l - 1], &e[l - 1], &d__[l], &rt1, &rt2, &cos, &sin);
                work[m] = cos;
                work[*n - 1 + m] = sin;
                clasr_RVF(*n, C2, &work[m], &work[*n - 1 + m], &z__[(l - 1) * z_dim1 + 1], *ldz);
            } 
            else 
            {
                slae2_(&d__[l - 1], &e[l - 1], &d__[l], &rt1, &rt2);
            }
            d__[l - 1] = rt1;
            d__[l] = rt2;
            e[l - 1] = 0.f;
            l += -2;
            if (l >= lend) 
            {
                goto L90;
            }
            goto L140;
        }

        if (jtot == nmaxit) 
        {
            goto L140;
        }
        ++jtot;
/*        Form shift. */
        g = (d__[l - 1] - p) / (e[l - 1] * 2.f);
        r__ = slapy2_(&g, &c_b41);
        g = d__[m] - p + e[l - 1] / (g + r_sign(&r__, &g));

        sin = 1.f;
        cos = 1.f;
        p = 0.f;
/*        Inner loop */
        lm1 = l - 1;
        I1 = lm1;
        for (i__ = m; i__ <= I1; ++i__) 
        {
            f = sin * e[i__];
            b = cos * e[i__];
            slartg_x(g, f, &cos, &sin, &r__);  //slartg_(&g, &f, &cos, &sin, &r__);
            if (i__ != m) 
            {
                e[i__ - 1] = r__;
            }
            g = d__[i__] - p;
            r__ = (d__[i__ + 1] - g) * sin + cos * 2.f * b;
            p = sin * r__;
            d__[i__] = g + p;
            g = cos * r__ - b;
/*           If eigenvectors are desired, then save rotations. */
            if (icompz > 0) 
            {
                work[i__] = cos;
                work[*n - 1 + i__] = sin;
            }
        }
/*        If eigenvectors are desired, then apply saved rotations. */
        if (icompz > 0) 
        {
            mm = l - m + 1;
            clasr_RVF(*n, mm, &work[m], &work[*n - 1 + m], &z__[m * z_dim1 + 1], *ldz);
        }

        d__[l] -= p;
        e[lm1] = g;
        goto L90;
/*        Eigenvalue found. */
L130:
        d__[l] = p;

        --l;
        if (l >= lend) 
        {
            goto L90;
        }
        goto L140;
    }
/*     Undo scaling if necessary */
L140:
    if (iscale == 1) 
    {
        I1 = lendsv - lsv + 1;
        slascl_("G", &C0, &C0, &ssfmax, &anorm, &I1, &C1, &d__[lsv], n, info);
        I1 = lendsv - lsv;
        slascl_("G", &C0, &C0, &ssfmax, &anorm, &I1, &C1, &e[lsv], n, info);
    } 
    else if (iscale == 2) 
    {
        I1 = lendsv - lsv + 1;
        slascl_("G", &C0, &C0, &ssfmin, &anorm, &I1, &C1, &d__[lsv], n, info);
        I1 = lendsv - lsv;
        slascl_("G", &C0, &C0, &ssfmin, &anorm, &I1, &C1, &e[lsv], n, info);
    }
/*     Check for no convergence to an eigenvalue after a total */
/*     of N*MAXIT iterations. */
    if (jtot == nmaxit) 
    {
        I1 = *n - 1;
        for (i__ = 1; i__ <= I1; ++i__) 
        {
            if (e[i__] != 0.f) 
            {
                ++(*info);
            }
        }
        return 0;
    }
    goto L10;
    
/*     Order eigenvalues and eigenvectors. */
L160:
    if (icompz == 0) 
    {
        slasrt_("I", n, &d__[1], info);
    } 
    else 
    {
        I1 = *n;
        for (ii = 2; ii <= I1; ++ii) 
        {
            i__ = ii - 1;
            k = i__;
            p = d__[i__];
            I2 = *n;
            for (j = ii; j <= I2; ++j) 
            {
                if (d__[j] < p) 
                {
                    k = j;
                    p = d__[j];
                }
            }
            if (k != i__) 
            {
                d__[k] = d__[i__];
                d__[i__] = p;
                cswap_(n, &z__[i__ * z_dim1 + 1], &C1, &z__[k * z_dim1 + 1], &C1);
            }
        }
    }
    return 0;
} /* csteqr_ */
