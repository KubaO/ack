21800 #include "rundecs.h"
21810     (*  COPYRIGHT 1983 C.H.LINDSEY, UNIVERSITY OF MANCHESTER  *)
21820 (**)
21830 (**)
21840 (*-01() (*-05()
21850 FUNCTION COLLTS(TEMP: NAKEGER; UNIT: A68INT; OFFSET: OFFSETRANGE): ASNAKED;
21860 (*PCOLLTOTAL - USUALLY CODED INLINE*)
21870   VAR OBJECT: UNDRESSP;
21880     BEGIN WITH TEMP DO WITH NAK DO
21890       BEGIN
21900       OBJECT := INCPTR(POINTER, OFFSET);
21910       OBJECT^.FIRSTINT := UNIT;
21920       COLLTS := ASNAK;
21930       END
21940     END;
21950 (**)
21960 (**)
21970 FUNCTION COLLTS2(TEMP: NAKEGER; UNIT: A68LONG; OFFSET: OFFSETRANGE): ASNAKED;
21980 (*PCOLLTOTAL+1 - USUALLY CODED INLINE*)
21990   VAR OBJECT: UNDRESSP;
22000     BEGIN WITH TEMP DO WITH NAK DO
22010       BEGIN
22020       OBJECT := INCPTR(POINTER, OFFSET);
22030       OBJECT^.FIRSTLONG := UNIT;
22040       COLLTS2 := ASNAK;
22050       END
22060     END;
22070 (**)
22080 (**)
22090 FUNCTION COLLTPT(TEMP: NAKEGER; UNIT: OBJECTP; OFFSET: OFFSETRANGE): ASNAKED;
22100 (*PCOLLTOTAL+2 - USUALLY CODED INLINE*)
22110   VAR OBJECT: UNDRESSP ;
22120     BEGIN WITH TEMP DO WITH NAK DO
22130       BEGIN
22140       OBJECT := INCPTR(POINTER, OFFSET);
22150       WITH OBJECT^ DO
22160         BEGIN FIRSTPTR := UNIT; WITH FIRSTPTR^ DO FINC END;
22170       COLLTPT := ASNAK;
22180       END
22190     END;
22200 (**)
22210 (**)
22220 ()-05*) ()-01*)
22230 (**)
22240 (**)
22250 (*-02() BEGIN END ; ()-02*)
22260 (*+01()
22270 BEGIN (*OF MAIN PROGRAM*)
22280 END (*OF EVERYTHING*).
22290 ()+01*)
