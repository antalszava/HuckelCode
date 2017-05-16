      SUBROUTINE CCHOL(N,ND,A,FAIL)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION A(ND,ND)
      integer FAIL
C
C
C SUBROUTINE CCHOL COMPUTES CHOLESKI
C DECOMPOSITION OF GIVEN COMPLEX POSITIVE DEFINITE
C MATRIX A.
C
C INPUT DATA
C
C  N --- ORDER OF MATRIX
C  ND -- DIMENSION OF ARRAY A (IT CAN BE
C        GREATER THAN OR EQUAL TO N)
C  A --- GIVEN MATRIX
C        IT IS SUPPOSED TO BE STORED IN THE
C        FOLLOWING WAY.  DIAGONAL ELEMENTS,
C        BEING REAL, ARE STORED ON THE DIAGONAL,
C        REAL PARTS OF OFFDIAGONAL ELEMENTS
C        ARE STORED IN THE LOWER TRIANGLE OF A,
C        IMAG PARTS OF THE LOWER TRIANGLE ARE
C        STORED IN THE UPPER TRIANGLE OF A.
C
C     EXIT INFORMATION
C
C  A --- COMPLEX ELEMENTS OF MATRIX L, DEFINED BY
C     A=L*L(H)
C        ARE STORED IN THE SAME WAY AS ORIGINAL
C        ELEMENTS OF A, THAT IS REAL PARTS OF THE
C        LOWER TRIANGLE OF L IN THE LOWER TRIANGLE
C        OF A AND THE CORRESPONDING IMAG PARTS IN
C        THE UPPER TRIANGLE OF A.
C  FAIL --- IS SET TO ZERO IF THE DECOMPOSITION WAS
C           SUCCESFUL AND TO NONZERO IF
C           THE MATRIX WAS NOT POSITIVE DEFINITE.
C
C
C    PROGRAMMED BY E. ZAKRAJSEK
C     JUNE 20, 1974
C
C
C
C     SUPPOSE DECOMPOSITION WILL FAIL
C
      FAIL=1
C
      DO 13 I=1,N
C
C     TEST FOR POSITIVE DEFINITNESS
C
      IF(A(I,I).LE.0.0D0) RETURN
C
C      COMPUTE COLUMN I
C
      A(I,I)=DSQRT(A(I,I))
      IF(I.EQ.N) GO TO 13
      IA=I+1
      DO 10 J=IA,N
      A(J,I)=A(J,I)/A(I,I)
   10 A(I,J)=A(I,J)/A(I,I)
C
C     REDUCE REMAINING COLUMNS
C
      DO 12 K=IA,N
      A(K,K)=A(K,K)-A(K,I)*A(K,I)-A(I,K)*A(I,K)
      IF(K.EQ.N) GO TO 12
      KA=K+1
      DO 11 J=KA,N
      A(J,K)=A(J,K)-A(J,I)*A(K,I)-A(I,J)*A(I,K)
   11 A(K,J)=A(K,J)-A(I,J)*A(K,I)+A(J,I)*A(I,K)
   12 CONTINUE
   13 CONTINUE
      FAIL=0
      RETURN
      END
      SUBROUTINE CTRED2(N,ND,A,B,D,E,F)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION A(ND,ND),B(ND,ND),D(ND),E(ND),F(ND)
C
C
C     SUBROUTINE CTRED2 REDUCES GIVEN COMPLEX
C     HERMITIAN MATRIX TO A TRIDIAGONAL FORM
C
C     PARAMETERS
C
C     N    --- ORDER OF THE MATRIX
C     ND   --- DIMENSION OF ARRAYS A AND B
C     A    --- GIVEN MATRIX, REPLACED BY REAL PART
C              OF THE TRANSFORMATION MATRIX
C     B    --- IMAG PART OF TRANSFORMATION MATRIX
C     D    --- DIAGONAL PART OF THE TRIADIAGONAL MATRIX
C     E    --- REAL PART OF THE CODIAGONAL OF THE
C              TRIDIAGONAL MATRIX
C              (LAST N-1 LOCATIONS)
C     F    --- IMAG PARTS OF THE LOWER CODIAGONAL.
C
C     THE GIVEN MATRIX SHOULD BE STORED IN THE
C     FOLLOWING WAY
C
C          --- DIAGONAL ELEMENTS IN THE DIAGONAL
C          --- REAL PART OF THE LOWER TRIANGLE IN THE
C              LOWER TRIANGLE
C          --- IMAG PARTS OF THE LOWER TRIANGLE
C              IN THE UPPER TRIANGLE
C
C
C     PROGRAMMED BY E. ZAKRAJSEK
C     JUNE 20,1974
C
C
C
      CHEP=2.0D0**(-56)
      D(1)=A(1,1)
      IF(N.EQ.1) GO TO 31
C
C MAIN K LOOP
C
      DO 30 K=2,N
      L=K-1
C
C     COMPUTE NORM
C
      ALL=0.D0
      DO 10 I=K,N
   10 ALL=ALL+A(I,L)*A(I,L) + A(L,I)*A(L,I)
      ALL=DSQRT(ALL)
C
C     COMPUTE CONSTANTS
C
      C=1.0D0
      S=0.D0
      R = DSQRT(A(K,L)*A(K,L) + A(L,K)*A(L,K))
      IF(DABS(R).LT.1.D-50) R=0.D0
      IF(R.EQ.0.0D0) GOTO 11
      C=A(K,L)/R
      S=A(L,K)/R
   11 ALR=ALL*C
      ALI=ALL*S
      A(L,L)=0.0D0
C
C     TEST FOR SUPERFLUOUS TRANSFORMATION
C
      SM=ALL*(ALL+R)
      IF(DABS(SM).LT.1.D-50) SM=0.D0
      IF(SM.EQ.0.D0) GO TO 20
      G=1.0D0/SM
      A(L,L)=G
C
      A(K,L)=A(K,L)+ALR
      A(L,K) =A(L,K)+ALI
C
C     NOW COMPUTE U=A*W
C     AND STORE INTO (E,F)
C
      T=0.0D0
      DO 16 I=K,N
      C=A(I,I)*A(I,L)
      S=A(I,I)*A(L,I)
      IF(I.EQ.K)GOTO 13
      IA=I-1
      DO 12 J=K,IA
      C=C+A(I,J)*A(J,L)-A(J,I)*A(L,J)
   12 S=S+A(I,J)*A(L,J)+A(J,I)*A(J,L)
   13 IF(I.EQ.N) GOTO 15
      IA=I+1
      DO 14 J=IA,N
      C=C+A(J,I)*A(J,L)+A(I,J)*A(L,J)
   14 S=S+A(J,I)*A(L,J)-A(I,J)*A(J,L)
   15 E(I)=G*C
      F(I)=G*S
   16 T=T+A(I,L)*C+A(L,I) *S
      T=T*(G*G)
C
C    TRANSFORM  MATRIX
C
      DO 18 I=K,N
      A(I,I)=A(I,I)-2.0D0*(A(I,L)*E(I)+A(L,I)*F(I))+
     *      T*(A(I,L)*A(I,L)+A(L,I)*A(L,I))
      IF(I.EQ.K) GOTO 18
      IA=I-1
      DO 17 J=K,IA
      A(I,J)=A(I,J)-A(I,L)*E(J)-A(L,I)*F(J)
     *      -A(J,L)*E(I)-A(L,J)*F(I)
     *      +T*(A(I,L)*A(J,L)+A(L,I)*A(L,J))
      A(J,I)=A(J,I)-A(L,I)*E(J)+A(I,L)*F(J)
     *      +A(L,J)*E(I)-A(J,L)*F(I)
     *      +T*(A(L,I)*A(J,L)-A(I,L)*A(L,J))
   17 CONTINUE
   18 CONTINUE
C
C     STORE DIAGONAL AND CODIAGONAL ELEMENTS
C
   20 D(K)=A(K,K)
      E(K)=-ALR
      F(K)=-ALI
   30 CONTINUE
C
C     NOW ACCUMULATE TRANSFORMATIONS
C
   31 A(N,N)=1.D0
      B(N,N)=0.D0
      IF(N.EQ.1) RETURN
      DO 40 KK=2,N
      K=N-KK+2
      L=K-1
C
C     SKIP TRANSFORMATION IF UNIT
C
      IF(DABS(A(L,L)).LT.1.D-50) A(L,L)=0.D0
      IF(A(L,L).EQ.0.0D0) GO TO 36
C
C     COMPUTE PRODUCT
C
      DO 35 J=K,N
      C=0.D0
      S=0.D0
      DO 33 I=K,N
      C=C+A(I,L)*A(I,J)+A(L,I)*B(I,J)
   33 S=S+A(I,L)*B(I,J)-A(L,I)*A(I,J)
      C=C*A(L,L)
      S=S*A(L,L)
      DO 34 I=K,N
      A(I,J)=A(I,J)-C*A(I,L)+S*A(L,I)
   34 B(I,J)=B(I,J)-C*A(L,I)-S*A(I,L)
   35 CONTINUE
C
C     MAKE NEW LINE
C
   36 DO 37 I=K,N
      A(I,L)=0.D0
      A(L,I)=0.D0
      B(I,L)=0.D0
   37 B(L,I)=0.D0
      A(L,L)=1.D0
      B(L,L)=0.D0
   40 CONTINUE
      RETURN
      END
      SUBROUTINE CTQL2(N,ND,D,E,F,A,B,FAIL)
      IMPLICIT REAL*8(A-H,O-Z)
      DIMENSION A(ND,ND), B(ND,ND), D(ND), E(ND), F(ND)
      integer FAIL
C
C
C     SUBROUTINE CTQL2 COMPUTES THE EIGENVALUES AND
C     EIGENVECTORS OF A COMPLEX HERMITIAN TRIDIAGONAL
C     MATRIX
C
C     PARAMETERS
C
C     N    --- ORDER OF MATRIX
C     ND   --- DIMENSION OF A AND B
C     D    --- DIAGONAL GIVEN
C     E    --- REAL PART OF CODIAGONAL GIVEN
C              (LAST N-1 LOCATIONS)
C     F    --- IMAG PART OF THE LOWER CODIAGONAL
C     A    --- REAL PART OF EIGENVECTORS
C     B    --- IMAG PART OF EIGENVECTORS
C     FAIL --- RECEIVES VALUE OF 1 INSTEAD OF ZERO
C              IF SOME EIGENVALUE TAKES MORE THAN 30
C              ITERATIONS.
C
C
C     EIGENVALUES ARE OBTAINED IN INCREASING OF
C     MAGNITUDE IN VECTOR D, EIGENVECTORS ARE STORED
C     BY COLUMNS.  ARRAYS A AND B SHOULD BE PRESET TO
C     SOME UNITARY MATRIX SUCH AS THE IDENTITY MATRIX
C     OR THE MATRIX PRODUCED BY CTRED2.
C
C
C     PROGRAMMED BY E.  ZAKRAJSEK
C     JUNE 21, 1974
C
C
C
C
C     ***************************************
C     *                                     *
C     * NEXT LINE OF PROGRAM DEFINES        *
C     * MACHINE DEPENDENT CONSTANT CHEP     *
C     * DEFINED AS THE SMALLEST REAL        *
C     * NUMBER FOR WHICH                    *
C     *                                     *
C     *        1.0+CHEP .GT. 1.0            *
C     *                                     *
C     ***************************************
C
      CHEP=2.0D0**(-56)
C
C     FIRST MAKE REAL CODIAGONAL MOVED DOWN
C     TO FIRST LOCATION
C
      IF(N.EQ.1) GO TO 12
      DO 11 K=2,N
      R=DSQRT(E(K)*E(K)+F(K)*F(K))
      IF(DABS(R).LT.1.D-50) R=0.D0
      IF(R.EQ.0.0D0) GO TO 11
      C=E(K)/R
      S=F(K)/R
C
C     ACCUMULATE ROTATION
C
      DO 10 I=1,N
      P=A(I,K)*C-B(I,K)*S
      B(I,K)=A(I,K)*S+B(I,K)*C
   10 A(I,K)=P
C
C     TRANSFORM NEXT E
C
      IF(K.EQ.N) GO TO 11
      L=K+1
      P=E(L)*C-F(L)*S
      F(L)=E(L)*S+F(L)*C
      E(L)=P
   11 E(K-1)=R
   12 E(N)=0.D0
C
C     INITIALIZE
C
      BB=0.D0
      FF=0.D0
      FAIL=1
C
C     MAIN LOOP
C
      DO 32 L=1,N
      J=0
      H=CHEP*(DABS(D(L))+DABS(E(L)))
      IF(BB.LT.H) BB=H
C
C     LOOK FOR SMALL SUBDIAGONAL ELEMENT
C
      DO 20 M=L,N
      IF(DABS(E(M)).LE.BB) GO TO 21
   20 CONTINUE
   21 IF(M.EQ.L) GO TO 31
C
C     NEXT ITERATION
C
   24 IF(J.EQ.30) RETURN
      J=J+1
C
C     FORM SHIFT
C
      P=(D(L+1)-D(L))/(2.0D0*E(L))
      R=DSQRT(1.0D0+P*P)
      H=D(L)-E(L)/(P+DSIGN(R,P))
C
      DO 25 I=L,N
   25 D(I)=D(I)-H
      FF=FF+H
C
C     QL TRANSFORMATION
C
      P=D(M)
      C=1.0D0
      S=0.0D0
      MA=M-1
C
      DO 30 IA=L,MA
      I=MA-IA+L
      I1=I+1
      G=C*E(I)
      H=C*P
      IF(DABS(P).LT.DABS(E(I))) GO TO 26
C
      C=E(I)/P
      R=DSQRT(C*C+1.0D0)
      E(I1 )=S*P*R
      S=C/R
      C=1.0D0/R
      GO TO 27
C
   26 C=P/E(I)
      R=DSQRT(C*C+1. D0)
      E(I1 )=S*E(I)*R
      S=1.0D0/R
      C=C/R
C
   27 P=C*D(I)-S*G
      D(I1 )=H+S*(C*G+S*D(I))
C
C     FORM VECTOR
C
      DO 28 K=1,N
      HR=A(K,I1 )
      HI=B(K,I1 )
      A(K,I1 )=S*A(K,I)+C*HR
      B(K,I1 )=S*B(K,I)+C*HI
      A(K,I)=C*A(K,I)-S*HR
   28 B(K,I)=C*B(K,I)-S*HI
C
   30 CONTINUE
C
      E(L)=S*P
      D(L)=C*P
      IF(DABS(E(L)).GT.BB) GO TO 24
C
C     ROOT FOUND
C
   31 D(L)=D(L)+FF
   32 CONTINUE
C
C     ORDER EIGENVALUES AND EIGENVECTORS
C
      DO 42 I=1,N
      K=I
      DO 40 J=I,N
      IF(D(J).LT.D(K)) K=J
   40 CONTINUE
C
C
      IF(K.EQ.I) GO TO 42
      P=D(I)
      D(I)=D(K)
      D(K)=P
C
      DO 41 J=  1,N
      P=A(J,I)
      A(J,I)=A(J,K)
      A(J,K)=P
C
      P=B(J,I)
      B(J,I)=B(J,K)
   41 B(J,K)=P
   42 CONTINUE
      FAIL=0
      RETURN
      END
