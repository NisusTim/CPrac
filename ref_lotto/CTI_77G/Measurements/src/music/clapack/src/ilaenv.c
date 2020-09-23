#include "f2c.h"
#include "string.h"

/* Table of constant values */

static integer c__0 = 0;
static real c_b163 = 0.f;
static real c_b164 = 1.f;
static integer c__1 = 1;

#define _G		0x47
#define _M      0x4d

#define _BR     0x4252
#define _GB     0x4742
#define _GE     0x4745
#define _HE     0x4845
#define _HR     0x4852
#define _LA     0x4c41
#define _LQ     0x4c51
#define _OR     0x4f52
#define _PB     0x5042
#define _PO     0x504f
#define _QL     0x514c
#define _QR     0x5152
#define _RQ     0x5251
#define _ST     0x5354
#define _SY     0x5359
#define _TR     0x5452
#define _UN     0x554e

#define _BRD    0x425244
#define _EBZ    0x45425a
#define _GST    0x475354
#define _HRD    0x485244
#define _LQF    0x4c5146
#define _QLF    0x514c46
#define _QRF    0x515246
#define _RQF    0x525146
#define _TRD    0x545244
#define _TRF    0x545246
#define _TRI    0x545249
#define _UUM    0x55554d

    extern integer iparmq_(integer *, char *, char *, integer *, integer *, integer *, integer *);
    extern integer ieeeck_(integer *, real *, real *);

integer ilaenv_(integer *ispec, char *name__, char *opts, integer *n1, 
	integer *n2, integer *n3, integer *n4)
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
     integer c2, c3, c4, c30;
     integer nb, nx;
     logical cname;
     integer nbmin;
     logical sname;
     char subnam[6];

/*  -- LAPACK auxiliary routine (version 3.1.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     January 2007 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ILAENV is called from the LAPACK routines to choose problem-dependent */
/*  parameters for the local environment.  See ISPEC for a description of */
/*  the parameters. */

/*  ILAENV returns an INTEGER */
/*  if ILAENV >= 0: ILAENV returns the value of the parameter specified by ISPEC */
/*  if ILAENV < 0:  if ILAENV = -k, the k-th argument had an illegal value. */

/*  This version provides a set of parameters which should give good, */
/*  but not optimal, performance on many of the currently available */
/*  computers.  Users are encouraged to modify this subroutine to set */
/*  the tuning parameters for their particular machine using the option */
/*  and problem size information in the arguments. */

/*  This routine will not function correctly if it is converted to all */
/*  lower case.  Converting it to all upper case is allowed. */

/*  Arguments */
/*  ========= */

/*  ISPEC   (input) INTEGER */
/*          Specifies the parameter to be returned as the value of */
/*          ILAENV. */
/*          = 1: the optimal blocksize; if this value is 1, an unblocked */
/*               algorithm will give the best performance. */
/*          = 2: the minimum block size for which the block routine */
/*               should be used; if the usable block size is less than */
/*               this value, an unblocked routine should be used. */
/*          = 3: the crossover point (in a block routine, for N less */
/*               than this value, an unblocked routine should be used) */
/*          = 4: the number of shifts, used in the nonsymmetric */
/*               eigenvalue routines (DEPRECATED) */
/*          = 5: the minimum column dimension for blocking to be used; */
/*               rectangular blocks must have dimension at least k by m, */
/*               where k is given by ILAENV(2,...) and m by ILAENV(5,...) */
/*          = 6: the crossover point for the SVD (when reducing an m by n */
/*               matrix to bidiagonal form, if max(m,n)/min(m,n) exceeds */
/*               this value, a QR factorization is used first to reduce */
/*               the matrix to a triangular form.) */
/*          = 7: the number of processors */
/*          = 8: the crossover point for the multishift QR method */
/*               for nonsymmetric eigenvalue problems (DEPRECATED) */
/*          = 9: maximum size of the subproblems at the bottom of the */
/*               computation tree in the divide-and-conquer algorithm */
/*               (used by xGELSD and xGESDD) */
/*          =10: ieee NaN arithmetic can be trusted not to trap */
/*          =11: infinity arithmetic can be trusted not to trap */
/*          12 <= ISPEC <= 16: */
/*               xHSEQR or one of its subroutines, */
/*               see IPARMQ for detailed explanation */

/*  NAME    (input) CHARACTER*(*) */
/*          The name of the calling subroutine, in either upper case or */
/*          lower case. */

/*  OPTS    (input) CHARACTER*(*) */
/*          The character options to the subroutine NAME, concatenated */
/*          into a single character string.  For example, UPLO = 'U', */
/*          TRANS = 'T', and DIAG = 'N' for a triangular routine would */
/*          be specified as OPTS = 'UTN'. */

/*  N1      (input) INTEGER */
/*  N2      (input) INTEGER */
/*  N3      (input) INTEGER */
/*  N4      (input) INTEGER */
/*          Problem dimensions for the subroutine NAME; these may not all */
/*          be required. */

/*  Further Details */
/*  =============== */

/*  The following conventions have been used when calling ILAENV from the */
/*  LAPACK routines: */
/*  1)  OPTS is a concatenation of all of the character options to */
/*      subroutine NAME, in the same order that they appear in the */
/*      argument list for NAME, even if they are not used in determining */
/*      the value of the parameter specified by ISPEC. */
/*  2)  The problem dimensions N1, N2, N3, N4 are specified in the order */
/*      that they appear in the argument list for NAME.  N1 is used */
/*      first, N2 second, and so on, and unused problem dimensions are */
/*      passed a value of -1. */
/*  3)  The parameter value returned by ILAENV is checked for validity in */
/*      the calling subroutine.  For example, ILAENV is used to retrieve */
/*      the optimal blocksize for STRTRI as follows: */

/*      NB = ILAENV( 1, 'STRTRI', UPLO // DIAG, N, -1, -1, -1 ) */
/*      IF( NB.LE.1 ) NB = MAX( 1, N ) */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    switch (*ispec) {
	case 1:  goto L10;
	case 2:  goto L10;
	case 3:  goto L10;
	case 4:  goto L80;
	case 5:  goto L90;
	case 6:  goto L100;
	case 7:  goto L110;
	case 8:  goto L120;
	case 9:  goto L130;
	case 10:  goto L140;
	case 11:  goto L150;
	case 12:  goto L160;
	case 13:  goto L160;
	case 14:  goto L160;
	case 15:  goto L160;
	case 16:  goto L160;
    }

/*     Invalid value for ISPEC */

    ret_val = -1;
    return ret_val;

L10:

/*     Convert NAME to upper case if the first character is lower case. */

    ret_val = 1;
    
    memcpy(subnam, name__, 6);

    c2 = subnam[1];
    c2 = (c2 << 8) + subnam[2];
    c30 = subnam[3]; 
    c3 = (c30 << 8) + subnam[4];
    c3 = (c3 << 8) + subnam[5];
    c4 = subnam[4];
    c4 = (c4 << 8) + subnam[5];
    
    cname = subnam[0] == 'C' || subnam[0] == 'Z';
    sname = subnam[0] == 'S' || subnam[0] == 'D';

    switch (*ispec) {
	case 1:  goto L50;
	case 2:  goto L60;
	case 3:  goto L70;
    }

L50:

/*     ISPEC = 1:  block size */

/*     In these examples, separate code is provided for setting NB for */
/*     real and complex.  We assume that NB will take the same value in */
/*     single or double precision. */

    nb = 1;

    if (c2 == _GE) 
    {
	    if (c3 == _TRF) 
	    {
//	        if (sname)
//		        nb = 64;
//	        else
		        nb = 64;
	    } 
	    else if (c3 == _QRF || 
	             c3 == _RQF || 
		         c3 == _LQF || 
		         c3 == _QLF) 
	    {
//	        if (sname)
//		        nb = 32;
//	        else 
		        nb = 32;
	    } 
	    else if (c3 == _HRD) 
	    {
//	        if (sname)
//		        nb = 32;
//	        else
		        nb = 32;
	    } 
	    else if (c3 == _BRD) 
	    {
//	        if (sname)
//	    	    nb = 32;
//	        else
	    	    nb = 32;
	    } 
	    else if (c3 == _TRI) 
	    {
//	        if (sname)
//		        nb = 64;
//	        else
		        nb = 64;
	    }
    } 
    else if (c2 == _PO) 
    {
	    if (c3 == _TRF) 
	    {
//	        if (sname)
//		        nb = 64;
//	        else
		        nb = 64;
	    }
    } 
    else if (c2 == _SY) 
    {
	    if (c3 == _TRF) 
	    {
//	        if (sname) 
//		        nb = 64;
//	        else 
		        nb = 64;
	    } 
	    else if (sname && (c3 == _TRD)) 
	    {
	        nb = 32;
	    } 
	    else if (sname && (c3 == _GST)) 
	    {
	        nb = 64;
	    }
    } 
    else if (cname && (c2 == _HE)) 
    {
	    if (c3 == _TRF) 
	        nb = 64;
	    else if (c3 == _TRD) 
	        nb = 32;
	    else if (c3 == _GST) 
	        nb = 64;
   }
    else if (sname &&  c2 == _OR ) 
    {
        if (c30 == _G) 
        {
            if ( c4 == _QR  || 
                 c4 == _RQ  || 
                 c4 == _LQ  || 
                 c4 == _QL  || 
                 c4 == _HR  || 
                 c4 == _TR  || 
                 c4 == _BR ) 
            {
		nb = 32;
	    }
        } 
        else if (c30 == _M) 
        {
            if ( c4 == _QR  || 
                 c4 == _RQ  || 
                 c4 == _LQ  || 
                 c4 == _QL  || 
                 c4 == _HR  || 
                 c4 == _TR  || 
                 c4 == _BR ) 
            {
                nb = 32;
            }
        }
    }
    else if (cname &&  c2 == _UN ) 
    {
	    if (c30 == _G) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
		         c4 == _LQ  || 
		         c4 == _QL  || 
		         c4 == _HR  || 
		         c4 == _TR  || 
		         c4 == _BR ) 
	        {
		        nb = 32;
	        }
	    } 
	    else if (c30 == _M) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
		         c4 == _LQ  || 
		         c4 == _QL  || 
		         c4 == _HR  || 
		         c4 == _TR  || 
		         c4 == _BR ) 
	        {
		        nb = 32;
	        }
	    }
    } 
    else if ( c2 == _GB ) 
    {
	    if ( c3 == _TRF ) 
	    {
	        if (sname) 
	        {
		        if (*n4 <= 64) 
		            nb = 1;
		        else 
		            nb = 32;
	        } 
	        else 
	        {
		        if (*n4 <= 64) 
		            nb = 1;
		        else 
		            nb = 32;
	        }
	    }
    } 
    else if ( c2 == _PB ) 
    {
	    if ( c3 == _TRF ) 
	    {
	        if (sname) 
	        {
		        if (*n2 <= 64) 
		            nb = 1;
		        else 
		            nb = 32;
	        } 
	        else 
	        {
		        if (*n2 <= 64) 
		            nb = 1;
		        else 
		            nb = 32;
	        }
	    }
    } 
    else if ( c2 == _TR ) 
    {
	    if ( c3 == _TRI ) 
	    {
//	        if (sname) 
//		        nb = 64;
//	        else 
		        nb = 64;
	    }
    } 
    else if ( c2 == _LA ) 
    {
	    if ( c3 == _UUM ) 
	    {
//	        if (sname) 
//		        nb = 64;
//	        else 
		        nb = 64;
	    }
    } 
    else if (sname &&  c2 == _ST ) 
    {
	    if ( c3 == _EBZ ) 
	        nb = 1;
    }
    ret_val = nb;
    return ret_val;

L60:

/*     ISPEC = 2:  minimum block size */

    nbmin = 2;
    if ( c2 == _GE ) 
    {
	    if ( c3 == _QRF  || 
	         c3 == _RQF  || 
	         c3 == _LQF  || 
	         c3 == _QLF )
		{
//        if (sname) 
//		    nbmin = 2;
//	    else 
		    nbmin = 2;
    } 
	else if ( c3 == _HRD ) 
	{
//	    if (sname) 
//		    nbmin = 2;
//	    else 
		    nbmin = 2;
	} 
	else if ( c3 == _BRD ) 
	{
//	    if (sname) 
//		    nbmin = 2;
//	    else 
		    nbmin = 2;
	} 
	else if ( c3 == _TRI ) 
	{
//	    if (sname) 
//		    nbmin = 2;
//	    else 
		    nbmin = 2;
	}
    } 
    else if ( c2 == _SY ) 
    {
	    if ( c3 == _TRF ) 
	    {
//	        if (sname) 
//		        nbmin = 8;
//	        else 
		        nbmin = 8;
	    } 
	    else if (sname &&  c3 == _TRD ) 
	    {
	        nbmin = 2;
	    }
    } 
    else if (cname &&  c2 == _HE ) 
    {
	    if ( c3 == _TRD ) 
	    {
	        nbmin = 2;
	    }
    } 
    else if (sname &&  c2 == _OR ) 
    {
	    if (c30 == _G) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
	             c4 == _LQ  || 
	             c4 == _QL  || 
	             c4 == _HR  || 
	             c4 == _TR  || 
	             c4 == _BR ) 
	        {
		        nbmin = 2;
	        }
	    } 
	    else if (c30 == _M) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
	             c4 == _LQ  || 
	             c4 == _QL  || 
	             c4 == _HR  || 
	             c4 == _TR  || 
	             c4 == _BR ) 
	        {
		        nbmin = 2;
	        }
	    }
    } 
    else if (cname &&  c2 == _UN ) 
    {
	    if (c30 == _G) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
	             c4 == _LQ  || 
	             c4 == _QL  || 
	             c4 == _HR  || 
	             c4 == _TR  || 
	             c4 == _BR ) 
	        {
		        nbmin = 2;
	        }
	    } 
	    else if (c30 == _M) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
	             c4 == _LQ  || 
	             c4 == _QL  || 
	             c4 == _HR  || 
	             c4 == _TR  || 
	             c4 == _BR ) 
	        {
		        nbmin = 2;
	        }
	    }
    }
    ret_val = nbmin;
    return ret_val;

L70:

/*     ISPEC = 3:  crossover point */

    nx = 0;
    if ( c2 == _GE ) 
    {
	    if ( c3 == _QRF  || 
	         c3 == _RQF  || 
	         c3 == _LQF  || 
	         c3 == _QLF )
		{
	        if (sname) 
	        {
		        nx = 128;
	        } 
	        else 
	        {
		        nx = 128;
	        }
	    } 
	    else if ( c3 == _HRD ) 
	    {
	        if (sname) 
	        {
		        nx = 128;
	        } 
	        else 
	        {
		        nx = 128;
	        }
        } 
	    else if ( c3 == _BRD ) 
	    {
	        if (sname) 
	        {
		        nx = 128;
	        } 
	        else 
	        {
		        nx = 128;
	        }
	    }
    } 
    else if ( c2 == _SY ) 
    {
	    if (sname &&  c3 == _TRD ) 
	    {
	        nx = 32;
	    }
    } 
    else if (cname &&  c2 == _HE ) 
    {
	    if ( c3 == _TRD ) 
	    {
	        nx = 32;
	    }
    } 
    else if (sname &&  c2 == _OR ) 
    {
	    if (c30 == _G) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
	             c4 == _LQ  || 
	             c4 == _QL  || 
	             c4 == _HR  || 
	             c4 == _TR  || 
	             c4 == _BR ) 
	        {
		        nx = 128;
	        }
	    }
    } 
    else if (cname &&  c2 == _UN ) 
    {
	    if (c30 == _G) 
	    {
	        if ( c4 == _QR  || 
	             c4 == _RQ  || 
	             c4 == _LQ  || 
	             c4 == _QL  || 
	             c4 == _HR  || 
	             c4 == _TR  || 
	             c4 == _BR ) 
	        {
		        nx = 128;
	        }
	    }
    }
    ret_val = nx;
    return ret_val;

L80:

/*     ISPEC = 4:  number of shifts (used by xHSEQR) */

    ret_val = 6;
    return ret_val;

L90:

/*     ISPEC = 5:  minimum column dimension (not used) */

    ret_val = 2;
    return ret_val;

L100:

/*     ISPEC = 6:  crossover point for SVD (used by xGELSS and xGESVD) */

    ret_val = (integer) ((real) min(*n1,*n2) * 1.6f);
    return ret_val;

L110:

/*     ISPEC = 7:  number of processors (not used) */

    ret_val = 1;
    return ret_val;

L120:

/*     ISPEC = 8:  crossover point for multishift (used by xHSEQR) */

    ret_val = 50;
    return ret_val;

L130:

/*     ISPEC = 9:  maximum size of the subproblems at the bottom of the */
/*                 computation tree in the divide-and-conquer algorithm */
/*                 (used by xGELSD and xGESDD) */

    ret_val = 25;
    return ret_val;

L140:

/*     ISPEC = 10: ieee NaN arithmetic can be trusted not to trap */

/*     ILAENV = 0 */
    ret_val = 1;
    if (ret_val == 1) {
	ret_val = ieeeck_(&c__0, &c_b163, &c_b164);
    }
    return ret_val;

L150:

/*     ISPEC = 11: infinity arithmetic can be trusted not to trap */

/*     ILAENV = 0 */
    ret_val = 1;
    if (ret_val == 1) {
	ret_val = ieeeck_(&c__1, &c_b163, &c_b164);
    }
    return ret_val;

L160:

/*     12 <= ISPEC <= 16: xHSEQR or one of its subroutines. */

    ret_val = iparmq_(ispec, name__, opts, n1, n2, n3, n4);
    return ret_val;

/*     End of ILAENV */

} /* ilaenv_ */
