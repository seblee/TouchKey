        

message '***************************************************************'
message '*PROJECT NAME :USER PROGRAM CODE                              *'
message '*     VERSION :                                               *'
message '*     IC BODY :                                               *'
message '* ICE VERSION :                                               *'
message '*      REMARK :                                               *'
message '***************************************************************'

                INCLUDE USER_PROGRAM.INC

                PUBLIC  _USER_PROGRAM_INITIAL
                PUBLIC  _USER_PROGRAM 


                ;========================
                ;=USER DATA DEFINE      =
                ;========================
USER_PROGRAM_DATA   .SECTION   'DATA'

                ;=============================
                ;=TIMER1 INT VECTOR DEFINE   =
                ;=============================
                #define TIMER1_INT_LOCATION		001CH   ;PTM0 A TIMER INTERRUPT VECTOR
                #define TB1_INT_LOCATION		0020H   ;TIMER BASE 1 INTERRUPT VECTOR

TIMER1_INT_CS	.SECTION	AT TIMER1_INT_LOCATION	'CODE'



                ;========================
                ;=USER PROGRAM          =
                ;========================
USER_PROGRAM_CODE   .SECTION   'CODE'


_USER_PROGRAM_INITIAL:
				RET
;;***********************************************************                           
;;*SUB. NAME:USER_MAIN                                      *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************                           
                ;;********************
_USER_PROGRAM:  ;;USER PROGRAM ENTRY *
                ;;********************


                SNZ     _SCAN_CYCLEF
                JMP     _USER_PROGRAM_NEXT1

                ;-Read key status with bitmap
                CALL    _GET_KEY_BITMAP ;OUTPUT IN DATA_BUT[0];_DATA_BUF[1]
                mov     a, _DATA_BUF[0]

_USER_PROGRAM_NEXT1:
                RET

              
                RET

