99200 #include "rundecs.h"
99210     (*  COPYRIGHT 1983 C.H.LINDSEY, UNIVERSITY OF MANCHESTER  *)
99220 (**)
99230 (**)
99240 FUNCTION SUBFIXED(SIGN, BEFORE, POINT, AFTER  : INTEGER; VAR EXP: INTEGER; EXPNEEDED: BOOLEAN;
99250                 X: REALTEGER; R: BOOLEAN; VAR S: OBJECTP; START: INTEGER): BOOLEAN; EXTERN;
99260 PROCEDURE ERRORFILL(VAR S: OBJECTP; LENGTH: INTEGER); EXTERN;
99270 (**)
99280 (**)
99290 FUNCTION WHOLE(XMODE: INTEGER; VAL: REALTEGER; WIDTH: INTEGER): OBJECTP;
99300   VAR
99310     S: OBJECTP;
99320     SIGN, E: INTEGER;
99330   BEGIN
99340     SIGN := ORD((WIDTH>0) OR (VAL.INT<0));
99350     S := NIL;
99360     IF NOT SUBFIXED(SIGN,
99370                     ABS(WIDTH)-SIGN-ORD(WIDTH=0), (*-VE FOR WIDTH=0*)
99380                     0, 0, E, FALSE,
99390                     VAL, XMODE=2,
99400                     S, 1) THEN
99410       ERRORFILL(S, ABS(WIDTH)+ORD(WIDTH=0));
99420     WHOLE := S;
99430   END;
99440 (**)
99450 (**)
99460 (*-02()
99470 BEGIN (*OF A68*)
99480 END; (*OF A68*)
99490 ()-02*)
99500 (*+01()
99510 BEGIN (*OF MAIN PROGRAM*)
99520 END (* OF EVERYTHING *).
99530 ()+01*)
