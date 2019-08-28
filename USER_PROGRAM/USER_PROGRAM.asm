        

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
#DEFINE		DEBUG_TEST		0

;==============
;=I/O DEFINE  =
;==============
;-PA DEFINE
PAPU_DEF        EQU     00000000B
PAC_DEF_0		EQU     00000000B
PAC_DEF_1		EQU     10011010B
_DRV_COM0_C		EQU     PAC.7
_DRV_COM1_C		EQU     PAC.3
_DRV_COM2_C		EQU     PAC.4
_DRV_COM3_C		EQU     PAC.1
PA_DEF_0		EQU     00000000B
PA_DEF_1		EQU     10011010B
_DRV_COM0		EQU     PA.7
_DRV_COM1		EQU     PA.3
_DRV_COM2		EQU     PA.4
_DRV_COM3		EQU     PA.1

;-PB DEFINE
PBPU_DEF        EQU     00000000B
PBC_DEF         EQU     00000000B
PB_DEF          EQU     00000000B

;-PC DEFINE
PCPU_DEF        EQU     00000000B
PCC_DEF_0       EQU     00000000B
PCC_DEF_1       EQU     11111111B
_DRV_CS0_C      EQU     PCC.0
_DRV_CS1_C      EQU     PCC.1
_DRV_CS2_C      EQU     PCC.2
_DRV_CS3_C      EQU     PCC.3

PC_DEF_0		EQU     00000000B
PC_DEF_1		EQU     11111111B
_DRV_CS0		EQU     PC.0
_DRV_CS1		EQU     PC.1
_DRV_CS2		EQU     PC.2
_DRV_CS3		EQU     PC.3

DATA0_G			EQU     ACC.0
DATA1_F			EQU     ACC.1
DATA2_DP		EQU     ACC.2
DATA3_A			EQU     ACC.3
DATA4_B			EQU     ACC.4
DATA5_D			EQU     ACC.5
DATA6_C			EQU     ACC.6
DATA7_E			EQU     ACC.7



C_KEYON_count	EQU     012D
C_MultiKey_NO	EQU     03D

;;-STACK 
STACK           DB      4 DUP(?)
KEY_STATUS      DB      2 DUP(?)

KEYON_count		DB      ?
Bit_count		DB      ?
Key_Value_Copy	DB      ?
Key_Value		DB      ?

Key_Value1		DB      ?
temp_1			DB      ?
Time1S_L		DB      ?
Time1S_H		DB      ?

Key_Increment		EQU		Key_Value.0
Key_Stew			EQU		Key_Value.1
Key_Power			EQU		Key_Value.2
Key_HealthFry		EQU		Key_Value.3
Key_Intelligence	EQU		Key_Value.4
Key_ChildLock		EQU		Key_Value.5
Key_Preset			EQU		Key_Value.6
Key_Decrement		EQU		Key_Value.7

f_multiKey_pressed	DBit
f_delay_1s			DBIT

LED_SCAN_TASK	DB      ?
LED_REG			DB      ?
LED1_REG        DB      ?
LED2_REG        DB      ?
LED3_REG        DB      ?
LED4_REG        DB      ?
LED5_REG        DB      ?
LED6_REG        DB      ?
LED7_REG        DB      ?

LED1_REG0       DB      ?
LED2_REG0       DB      ?
LED3_REG0       DB      ?
LED4_REG0       DB      ?
LED5_REG0       DB      ?
LED6_REG0       DB      ?
LED7_REG0       DB      ?

;COM6 REGISTER FROM MASTER
LED00_HUOG		EQU		LED5_REG.0
LED01_JIANZ		EQU		LED5_REG.1
LED02_ZENGZ		EQU		LED5_REG.2
LED03_BAOT		EQU		LED5_REG.3
LED04_ZHUZ		EQU		LED5_REG.4
LED05_LIUC		EQU		LED5_REG.5
LED06_BIANC		EQU		LED5_REG.6
LED07_BAOC		EQU		LED5_REG.7

;COM7 REGISTER FROM MASTER
LED08_TONGS		EQU		LED6_REG.0
LED09_YUEY		EQU		LED6_REG.1
LED10_GONGL		EQU		LED6_REG.2
LED11_WEND		EQU		LED6_REG.3
LED12_YURE		EQU		LED6_REG.4
LED13_WENGH		EQU		LED6_REG.5
LED14_KAIG		EQU		LED6_REG.6
LED15_Reserved	EQU		LED6_REG.7


IIC_QUE_BUF     DB      11 DUP(?)
COMMAND         EQU     0
DATA1           EQU     1
DATA2           EQU     2
DATA3           EQU     3
DATA4           EQU     4
DATA5           EQU     5
DATA6           EQU     6
DATA7           EQU     7
DATA8           EQU     8
CHECK_SUM       EQU     9 
POINT           EQU     10

                ;=============================
                ;=TIMER1 INT VECTOR DEFINE   =
                ;=============================
                #define TIMER1_INT_LOCATION		001CH   ;PTM0 A TIMER INTERRUPT VECTOR
                #define TB1_INT_LOCATION		0020H   ;TIMER BASE 1 INTERRUPT VECTOR

TIMER1_INT_CS	.SECTION	AT TIMER1_INT_LOCATION	'CODE'
                JMP     _TIMER1_INT




                ;========================
                ;=USER PROGRAM          =
                ;========================
USER_PROGRAM_CODE   .SECTION   'CODE'

;;***********************************************************                           
;;*SUB. NAME:      _TIMER_INT                               *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************
_TIMER1_INT:             
                MOV     STACK[0],A              
                MOV     A,STATUS                
                MOV     STACK[1],A 
                
				sdz		Time1S_L
				jmp		SCAN_LED
				mov		a, 250
				mov		Time1S_L, a
				sdz		Time1S_H
				jmp		SCAN_LED
				mov		a, 5
				mov		Time1S_H, a
				sz		f_delay_1s
				jmp		$+3
				set		f_delay_1s
				jmp		$+2
				clr		f_delay_1s
				
                ;------------------
SCAN_LED:       ;-SCAN_LED FUNCTION
                ;------------------

                ;-MASK LED
                MOV     A,PAC_DEF_1
                MOV     PAC,A
                ;--
                MOV     A,PCC_DEF_1
                MOV     PCC,A
             ;   SET     PC
                ;--
                MOV     A,LED_SCAN_TASK
                AND     A,00000111B
                ADDM    A,PCL
                JMP     DRV_LED1
                JMP     DRV_LED2
                JMP     DRV_LED3
                JMP     DRV_LED4
                JMP     DRV_LED5
                JMP     DRV_LED6
                JMP     DRV_LED7
                JMP     DRV_LED8
                JMP     END_LED_SCAN
                                                
END_LED_SCAN:   ;-END OF LED SCAN               
                MOV     A,STACK[1]              
                MOV     STATUS,A                
                MOV     A,STACK[0]              
                RETI       
                  



                ;----------------      
                ;-LED SCAN TASK -      
                ;----------------      
DRV_LED1:       ;-COM0
				CLR		_DRV_COM0_C
				CLR		_DRV_COM0
                MOV     A,LED4_REG
                MOV     LED_REG,A
                JMP     COM_SCAN
                   
DRV_LED2:       ;-COM1
				CLR		_DRV_COM1_C
				CLR		_DRV_COM1
                MOV     A,LED2_REG
                MOV     LED_REG,A
                JMP     COM_SCAN
                   
DRV_LED3:       ;-COM2
				CLR		_DRV_COM2_C
				CLR		_DRV_COM2
                MOV     A,LED3_REG
                MOV     LED_REG,A
                JMP     COM_SCAN
                   
DRV_LED4:       ;-COM3	
				CLR		_DRV_COM3_C
				CLR		_DRV_COM3
                MOV     A,LED1_REG
                MOV     LED_REG,A
                JMP     COM_SCAN
                
COM_SCAN:                
                CLR		ACC                
                SZ		LED_REG.7
                SET		DATA0_G
                SZ		LED_REG.6
                SET		DATA1_F
                SZ		LED_REG.5
                SET		DATA2_DP
                SZ		LED_REG.0
                SET		DATA3_A
                SZ		LED_REG.3
                SET		DATA4_B
                SZ		LED_REG.4
                SET		DATA5_D
                SZ		LED_REG.2
                SET		DATA6_C
                SZ		LED_REG.1
                SET		DATA7_E
                mov		A, LED_REG
                MOV     PC,A
				CLR		PCC
                INC     LED_SCAN_TASK
                JMP     END_LED_SCAN
                   
DRV_LED5:       ;-CS0
                MOV     A,PA_DEF_0		;Output Low
                MOV     PA,A
                MOV     A,PAC_DEF_0		;Output Mode
                MOV     PAC,A 
                
                SZ		LED08_TONGS		;TongSuo - LED8
                SET		ACC.7
                SZ		LED09_YUEY		;Yuyue   - LED9
                SET		ACC.3
                SZ		LED10_GONGL		;Gonglv  - LED10
                SET		ACC.4
                SZ		LED11_WEND		;Wendu   - LED11
                SET		ACC.1 
                MOV     PA,A
                
				CLR		_DRV_CS0_C
				CLR		_DRV_CS0
                INC     LED_SCAN_TASK
                JMP     END_LED_SCAN
                   
DRV_LED6:       ;-CS1
                MOV     A,PA_DEF_0		;Output Low
                MOV     PA,A
                MOV     A,PAC_DEF_0		;Output Mode
                MOV     PAC,A 
                
                SZ		LED12_YURE		;YuRe     - LED12
                SET		ACC.7
                SZ		LED13_WENGH		;HuoLi    - LED13
                SET		ACC.3
                SZ		LED14_KAIG		;KaiGuan  - LED14
                SET		ACC.4
                SZ		LED15_Reserved	;Reserved - LED15
                SET		ACC.1 
                MOV     PA,A
                
				CLR		_DRV_CS1_C
				CLR		_DRV_CS1
                INC     LED_SCAN_TASK
                JMP     END_LED_SCAN
                   
DRV_LED7:       ;-CS2
                MOV     A,PA_DEF_0		;Output Low
                MOV     PA,A
                MOV     A,PAC_DEF_0		;Output Mode
                MOV     PAC,A 
                
                SZ		LED04_ZHUZ		;ZhuZhou - LED4
                SET		ACC.7
                SZ		LED05_LIUC		;LiuCao  - LED5
                SET		ACC.3
                SZ		LED06_BIANC		;BianCao - LED6
                SET		ACC.4
                SZ		LED07_BAOC		;BaoCao  - LED7
                SET		ACC.1 
                MOV     PA,A
                                
				CLR		_DRV_CS2_C
				CLR		_DRV_CS2
                INC     LED_SCAN_TASK
                JMP     END_LED_SCAN 
                        
DRV_LED8:       ;-CS3
                MOV     A,PA_DEF_0		;Output Low
                MOV     PA,A
                MOV     A,PAC_DEF_0		;Output Mode
                MOV     PAC,A 
                
                SZ		LED00_HUOG		;HuoGuo  - LED0
                SET		ACC.7
                SZ		LED01_JIANZ		;JianZha - LED1
                SET		ACC.3
                SZ		LED02_ZENGZ		;ZhenZhu - LED2
                SET		ACC.4
                SZ		LED03_BAOT		;BaoTan  - LED3
                SET		ACC.1 
                MOV     PA,A
                
				CLR		_DRV_CS3_C
				CLR		_DRV_CS3
                CLR     LED_SCAN_TASK
                JMP     END_LED_SCAN
                

                

;;***********************************************************                           
;;*SUB. NAME:USER INITIAL PROGRAM                           *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************                           
                      ;;************************
_USER_PROGRAM_INITIAL:;;* USER_PROGRAM_INITIAL *
                      ;;************************

                ;----------------
                ;-IO INITIAL  ---
                ;----------------
                ;-PA INITIAL
                MOV     A,PAPU_DEF
                MOV     PAPU,A
                MOV     A,PAC_DEF_1
                MOV     PAC,A
                MOV     A,PA_DEF_1
                MOV     PA,A
                ;-PB INITIAL
                MOV     A,PBPU_DEF
                MOV     PBPU,A
                MOV     A,PBC_DEF
                MOV     PBC,A
                MOV     A,PB_DEF
                MOV     PB,A
                ;-PC INITIAL
                MOV     A,PCPU_DEF
                MOV     PCPU,A
                MOV     A,PCC_DEF_1
                MOV     PCC,A
                MOV     A,PC_DEF_0
                MOV     PC,A


				CLR		INTC0
				CLR		INTC1
				
                ;----------------
                ;-I2C INITIAL ---
                ;----------------
                ;;//MOV     A,0A0H      ;DEVICE ADDRESS
                ;;//MOV     SIMA,A
                ;;//MOV     A,11000010B ;I2C Mode ,Enable SIM
                ;;//MOV     SIMC0,A
                ;;//MOV     A,00000011B
                ;;//MOV     SIMC1,A
                ;;//SET     I2CTOEN
                ;;//CLR     SIMF        ;Clear SIM interrupt request flag
                ;;//SET     SIME        ;Enable SIM Interrupt


                ;-------------------
                ;-TIMER INT. INITIAL
                ;-------------------
                				CLR		EMI
        				;----PTM0 initial----
                        MOV     A,00110000B             ;FH/64
                        MOV     PTM0C0,A
                        MOV     A,11000001B             ;Timer mode //  CCRA
                        MOV     PTM0C1,A

                IF      SystemClock == 2                ;16MHZ
                        MOV     A,LOW  250
                        MOV     PTM0AL,A
                        MOV     A,HIGH 250
                        MOV     PTM0AH,A
                ELSEIF  SystemClock == 1                ;12MHZ
                        MOV     A,LOW  187
                        MOV     PTM0AL,A
                        MOV     A,HIGH 187
                        MOV     PTM0AH,A
                ELSE                                    ;8MHZ
                        MOV     A,LOW  125
                        MOV     PTM0AL,A
                        MOV     A,HIGH 125
                        MOV     PTM0AH,A
                ENDIF 

		;				SET     PT0ON
		;				SET     PTMA0E

              ; ;------------------
              ; ;-TIME BASE INITIAL
              ; ;------------------ 
              ; MOV     A,11111101B     ;2MS IN 16MHZ
              ; MOV     TBC,A
              ; SET     TB0E


                ;-ENABLE GLOBE INT.
                SET     EMI

                CLR     LED_SCAN_TASK
				mov		a, 250
				mov		Time1S_L, a
				mov		a, 5
				mov		Time1S_H, a
                RET
                
                ;just for testing
                mov		a, 0ffh
                mov		led1_reg, a
                mov		a, 0ffh
                mov		led2_reg, a
                mov		a, 0ffh
                mov		led3_reg, a
                mov		a, 0ffh
                mov		led4_reg, a
                mov		a, 0ffh
                mov		led5_reg, a
                mov		a, 0ffh
                mov		led6_reg, a
                mov		a, 0ffh
                mov		led7_reg, a
                
                RET
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
                mov		key_value, a
                mov		key_value1, a
                
           ;     mov		KEY_STATUS[0], a
           ;     clr		KEY_STATUS[1]                
				CALL	KeyON_Handle		;;KEY Press DEBOUCE

	IF		DEBUG_TEST	==	1
				;;added on 2013-04-16
				sz		f_delay_1s
				jmp		_USER_PROGRAM_NEXT1
				
                SZ      Key_Value1
                JMP		$+3
				MOV 	A, temp_1
				jmp		_USER_PROGRAM_NEXT0
				
                SZ      Key_Value1.0
                mov		a, 0
                SZ      Key_Value1.1
                mov		a, 1
                SZ      Key_Value1.2
                mov		a, 2
                SZ      Key_Value1.3
                mov		a, 3
                SZ      Key_Value1.4
                mov		a, 4
                SZ      Key_Value1.5
                mov		a, 5
                SZ      Key_Value1.6
                mov		a, 6
                SZ      Key_Value1.7
                mov		a, 7                
                mov		temp_1, a
                
_USER_PROGRAM_NEXT0:
				call	_GET_ENV_VALUE
				
				mov		a, high SEG_TAB
				mov		tbhp, a
				MOV 	A, temp_1
				inc		acc
				and		a, 00fh
				add		a, offset SEG_TAB
				mov		tblp, a
				tabrdc 	led1_reg				;;COM1
				MOV 	A, _DATA_BUF[1]
				and		a, 00fh
				add		a, offset SEG_TAB
				mov		tblp, a
				tabrdc 	led2_reg				;;COM2
				MOV 	A, _DATA_BUF[0]
				swapa	acc
				and		a, 00fh
				add		a, offset SEG_TAB
				mov		tblp, a
				tabrdc 	led3_reg				;;COM3
				MOV 	A, _DATA_BUF[0]
				and		a, 00fh
				add		a, offset SEG_TAB
				mov		tblp, a
				tabrdc 	led4_reg				;;COM4
	ENDIF			

_USER_PROGRAM_NEXT1:
                RET

SEG_TAB:
				DC	00FAH, 0050H, 00B9H, 0079H, 0053H, 006BH, 00EBH, 0058H, 00FBH, 007BH, 00DBH, 00E3H, 00AAH, 00F1H, 00ABH, 008BH, 0001H, 00ABH, 0000H 
				;	 '0',   '1',  '2',   '3',   '4',    '5',   '6',   '7',   '8',   '9',   'A',   'B',   'C'    'D',   'E',   'F',  

              
                RET

;;***********************************************************                           
;;*SUB. NAME: KeyON_Handle                                  *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************                           
   
KeyON_Handle:
				MOV		A,	Key_Value
				XOR		A,	Key_Value_Copy
				SZ		Z
				JMP		LP_KeyON_Handle_0
				MOV		A,	Key_Value
				MOV		Key_Value_Copy,	A
				jmp		LP_KeyON_Handle_EXIT
				
	LP_KeyON_Handle_0:				
				INC		KEYON_count
				MOV		A,	KEYON_count
				SUB		A,	C_KEYON_count
				SNZ		C
				jmp		LP_KeyON_Handle_EXIT0
				
				clr		Bit_Count
				sz		Key_Power
				inc		Bit_Count
				sz		Key_HealthFry
				inc		Bit_Count
				sz		Key_Stew
				inc		Bit_Count
				sz		Key_Increment
				inc		Bit_Count
				sz		Key_Decrement
				inc		Bit_Count
				sz		Key_Preset
				inc		Bit_Count
				sz		Key_ChildLock
				inc		Bit_Count
				sz		Key_Intelligence
				inc		Bit_Count
				
				;x ?= 0
				sz		Bit_Count
				JMP		$+2
				JMP		LP_KeyON_Handle_OFF
				
				;x ?= 1
				mov		a, Bit_Count
				xor		a, 1
				sz		z
				JMP		LP_KeyON_Handle_1Key		;1Key on case
				set		f_multiKey_pressed
				
				;x ?= 2;
				mov		a, Bit_Count
				xor		a, 2
				sz		z
				JMP		LP_KeyON_Handle_2Key		;2Key on case
			
				;x >= 3;
				sz		Key_Power					;power key
				JMP		LP_KeyON_Handle_nKey1		;nKey on case with power key
			;	jmp		LP_KeyON_Handle_0Key
				JMP		LP_KeyON_Handle_Calibrate
				
		LP_KeyON_Handle_2Key:
				;x = 2;
				sz		Key_Power					;power key
				JMP		LP_KeyON_Handle_2Key1
				
				snz		Key_Increment				;Increment +
			;	jmp		LP_KeyON_Handle_0Key
				JMP		LP_KeyON_Handle_Calibrate
				snz		Key_Decrement				;Decrement -
			;	jmp		LP_KeyON_Handle_0Key
				JMP		LP_KeyON_Handle_Calibrate
				JMP		LP_KeyON_Handle_ON
				
		LP_KeyON_Handle_nKey1:
		LP_KeyON_Handle_2Key1:
			;	set		f_multiKey_pressed
				clr		Key_Value
				set		Key_Power					;only send power key			
				JMP		LP_KeyON_Handle_ON
								
		LP_KeyON_Handle_1Key:
				snz		f_multiKey_pressed
				jmp		LP_KeyON_Handle_ON
				snz		Key_Power					;added on 2013/7/15
				
		LP_KeyON_Handle_0Key:
				clr		key_value
				
	LP_KeyON_Handle_ON:
                MOV     A,	Key_Value
                MOV     KEY_STATUS[0],	A
                MOV     A,	00H
                MOV     KEY_STATUS[1],	A
				jmp		LP_KeyON_Handle_EXIT

	LP_KeyON_Handle_OFF:
				clr		f_multiKey_pressed
				clr		Key_Value_Copy
				CLR		KEY_STATUS[0]
				CLR		KEY_STATUS[1]
				jmp		LP_KeyON_Handle_EXIT
				
	LP_KeyON_Handle_Calibrate:
				set		_FORCE_CALIBRATEF
				
LP_KeyON_Handle_EXIT:
				CLR		KEYON_count
				
LP_KeyON_Handle_EXIT0:
				RET
	 

                


