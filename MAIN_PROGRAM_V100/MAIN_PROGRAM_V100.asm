        
message '****************************************************************'
message '*PROJECT NAME :MAIN PROGRAM V100                               *'
message '*     VERSION :V100                                            *'
message '* ICE VERSION :                                                *'
message '*      DATE   :20140331                                        *'
message '*      REMARK :                                                *'
message '****************************************************************'
                ;=INCLUDE REFERENCE FILE                                   
                INCLUDE MAIN_PROGRAM_V100.INC  
                PUBLIC  _LOAD_TKS_GLOBE_VARIES 
                PUBLIC  _LOAD_HXT_REFERENCE
         
         
                ;================================================
                ;=Compatable with old MAIN_PROGRAM.ASM version  =
                ;================================================
                ;=Define IC Body 
                ifdef   BS83A04A
                    ifndef  _BS83A04A_
                    #define _BS83A04A_
                    endif
                endif
                ;----------------------
                ifdef   BS83B08A
                    ifndef  _BS83B08A_
                    #define _BS83B08A_
                    endif
                endif
                ;----------------------
                ifdef   BS83B12A
                    ifndef  _BS83B12A_
                    #define _BS83B12A_
                    endif
                endif
                ;----------------------
                ifdef   BS83B16A
                    ifndef  _BS83B16A_
                    #define _BS83B16A_
                    endif
                endif
                ;----------------------
                ifdef   BS84B08A
                    ifndef  _BS84B08A_
                    #define _BS84B08A_
                    endif
                endif
                ;----------------------
                ifdef   BS84C12A
                    ifndef  _BS84C12A_
                    #define _BS84C12A_
                    endif
                endif
                ;----------------------
                ifdef   BS82B16 
                    ifndef  _BS82B16_  
                    #define _BS82B16_ 
                    endif
                endif
                ;----------------------
                ifdef   BS82C16A
                    ifndef  _BS82C16A_ 
                    #define _BS82C16A_
                    endif
                endif
                ;----------------------
                ifdef   BS82D20A
                    ifndef  _BS82D20A_ 
                    #define _BS82D20A_
                    endif
                endif
         
         
                ;=Define TouchIPamount , one Touch IP include 4 touch keys
                ifdef   _BS83A04A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   1
                    endif
                endif
                ;----------------------
                ifdef   _BS83B08A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   2
                    endif
                endif
                ;----------------------
                ifdef   _BS83B12A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   3
                    endif
                endif
                ;----------------------
                ifdef   _BS83B16A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   4
                    endif
                endif
                ;----------------------
                ifdef   _BS84B08A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   2
                    endif
                endif
                ;----------------------
                ifdef   _BS84C12A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   3
                    endif
                endif
                ;----------------------
                ifdef   _BS82B16_
                    ifndef  TouchIPamount
                    #define TouchIPamount   4
                    endif
                endif
                ;----------------------
                ifdef   _BS82C16A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   4
                    endif
                endif
                ;----------------------
                ifdef   _BS82D20A_
                    ifndef  TouchIPamount
                    #define TouchIPamount   5
                    endif
                endif
                ;----------------------








                ;========================================
                ;= ID body define check     =============
                ;========================================  
                ifdef   _BS83A04A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS83B08A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS83B12A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS83B16A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS84B08A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS84C12A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS82B16_ 
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS82C16A_
                    #define ICdefined
                endif
                ;----------------------
                ifdef   _BS82D20A_
                    #define ICdefined
                endif
                ;----------------------
                ifndef  ICdefined
                        errmessage 'No define IC body or IC not support '
                endif






         
         
                ;========================================
                ;= MACRO define for MCU hardware initial=
                ;========================================                                        
                MCU_HARDWARE_INITIAL    MACRO
                ;--------------------------------   
                ;-INITIAL FOR BS83A04A  ---------
                ;--------------------------------  
                ifdef   _BS83A04A_
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-CLEAR BANK0 060H~0FFH
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------   
                ;-INITIAL FOR BS83B08A  ---------
                ;--------------------------------  
                ifdef   _BS83B08A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-CLEAR BANK0 060H~0FFH
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS83B12A  --------- 
                ;--------------------------------  
                ifdef   _BS83B12A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-CLEAR BANK1 080H~0FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 060H~0FFH
                        CLR     BP
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS83B16A  ---------
                ;--------------------------------  
                ifdef   _BS83B16A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-CLEAR BANK1 080H~0FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 060H~0FFH
                        CLR     BP
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS84B08A  --------- 
                ;--------------------------------  
                ifdef   _BS84B08A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-DISABLE ADC
                        CLR     ACERL
                        MOV     A,01100000B
                        MOV     ADCR0,A
                        CLR     ADCR1
                        ;-CLEAR BANK1 080H~0FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 060H~0FFH
                        CLR     BP
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS84C12A  ---------
                ;--------------------------------  
                ifdef   _BS84C12A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-DISABLE ADC
                        CLR     ACERL
                        MOV     A,01100000B
                        MOV     ADCR0,A
                        CLR     ADCR1
                        ;-CLEAR BANK2 280H~2DFH
                        MOV     A,2
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK1 180H~1FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 060H~0FFH
                        CLR     BP    
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS82B16   ---------
                ;--------------------------------  
                ifdef   _BS82B16_ 
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A

                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
         
                        ;-CLEAR BANK2 280H~2FFH
                        MOV     A,2
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK1 180H~1FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 080H~0FFH
                        CLR     BP    
                        MOV     A,80H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS82C16A  ---------
                ;--------------------------------  
                ifdef   _BS82C16A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)&00110000B)                           
                        MOV     CTRL,A          ;BIT7=FSYSON                                
                        ;--                     ;BIT5:BIT4=00/11:8MHZ ; 01:12MHZ ; 10:16MHZ 
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-CLEAR BANK3 380H~2DFH
                        MOV     A,3
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK2 280H~2DFH
                        MOV     A,2
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK1 180H~1FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 080H~0FFH
                        CLR     BP    
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS82D20A  ---------
                ;--------------------------------
                ifdef   _BS82D20A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)&00110000B)                           
                        MOV     CTRL,A          ;BIT7=FSYSON                                
                        ;--                     ;BIT5:BIT4=00/11:8MHZ ; 01:12MHZ ; 10:16MHZ 
                        MOV     A,00000011B
                        MOV     SMOD,A
                        ;-WDT INITIAL USE 125/500MS WHEN ENABLE POWER SAVE MODE                                                                       
                      ;;MOV     A,01010011B     ;500   MS                                                                                             
                        MOV     A,01010010B     ;125   MS                                                                                             
                        MOV     WDTC,A
                        ;-IF POWER SAVING MODE ENABLE
                        if      PowerSave==1
                        SZ      TO
                        JMP     WDT_WAKEUP      ;IF WAKEUP BY WDT TIME OUT
                        endif
                        ;-CLEAR BANK5 580H~2DFH
                        MOV     A,5
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK4 480H~2DFH
                        MOV     A,4
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK3 380H~2DFH
                        MOV     A,3
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK2 280H~2DFH
                        MOV     A,2
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK1 180H~1FFH
                        MOV     A,1
                        MOV     BP,A
                        MOV     A,80H
                        CALL    CLEAR_RAM
                        ;-CLEAR BANK0 080H~0FFH
                        CLR     BP    
                        MOV     A,60H
                        CALL    CLEAR_RAM
                endif
         
                ENDM
         
         
         
         
                ;========================================
                ;= MACRO define for SYSTEM CLOCK reload =
                ;========================================                                        
                RELOAD_SYS_CLOCK    MACRO
                ;--------------------------------   
                ;-INITIAL FOR BS83A04A  ---------
                ;--------------------------------  
                ifdef   _BS83A04A_
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------   
                ;-INITIAL FOR BS83B08A  ---------
                ;--------------------------------  
                ifdef   _BS83B08A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS83B12A  --------- 
                ;--------------------------------  
                ifdef   _BS83B12A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS83B16A  ---------
                ;--------------------------------  
                ifdef   _BS83B16A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS84B08A  --------- 
                ;--------------------------------  
                ifdef   _BS84B08A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS84C12A  ---------
                ;--------------------------------  
                ifdef   _BS84C12A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS82B16   ---------
                ;--------------------------------  
                ifdef   _BS82B16_ 
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)^00110000B)&00110000B
                        MOV     CTRL,A
                        ;--
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS82C16A  ---------
                ;--------------------------------  
                ifdef   _BS82C16A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)&00110000B);|10000000B                
                        MOV     CTRL,A          ;BIT7=FSYSON                                
                        ;--                     ;BIT5:BIT4=00/11:8MHZ ; 01:12MHZ ; 10:16MHZ 
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ;--------------------------------  
                ;-INITIAL FOR BS82D20A  ---------
                ;--------------------------------  
                ifdef   _BS82D20A_
                        ;-SET SYSTEM CLOCK
                        MOV     A,((SystemClock<<4)&00110000B);|10000000B                
                        MOV     CTRL,A          ;BIT7=FSYSON                                
                        ;--                     ;BIT5:BIT4=00/11:8MHZ ; 01:12MHZ ; 10:16MHZ 
                        MOV     A,00000011B
                        MOV     SMOD,A
                endif
         
                ENDM



















                ;==============
                ;=DATA SETCTION
                ;==============
MAIN_DATA       .SECTION          'DATA'
POR_ID          DB      2 DUP(?)



                ;==============
                ;=CODE SETCTION
                ;==============
PROGRAM_ENTRY   .SECTION  AT 000H 'CODE'
                ;----------------
                ;-SET POR ID 1---
                ;----------------
                MOV     A,042H      ;ASCII = B
                SNZ     TO
                MOV     POR_ID[0],A
                JMP     PROGRAM_RESET

                ;==============
                ;=MAIN PROGRAM=
                ;==============
MAIN_PROGRAM    .SECTION          'CODE'

                ;;*********************** 
PROGRAM_RESET:  ;;* PROGRAM ENTRY ******* 
                ;;*********************** 
                ;----------------
                ;-SET POR ID 2---
                ;----------------
                MOV     A,053H      ;ASCII = S
                MOV     POR_ID[1],A


                ;---------------------                                                                                                          
                ;-MCU HARDWARE INITIAL
                ;--------------------- 
                MCU_HARDWARE_INITIAL

                ;------------------------------
                ;-LOAD LIBRARY OPTION/THRESHOLD
                ;------------------------------                                                                  
                CALL    _LOAD_TKS_GLOBE_VARIES

                ;------------------------
                ;-EXTEND FUNCTION INITIAL
                ;------------------------
                ifdef   EXTEND_FUNCTION_1A_INITIAL
                CALL    EXTEND_FUNCTION_1A_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1B_INITIAL
                CALL    EXTEND_FUNCTION_1B_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1C_INITIAL
                CALL    EXTEND_FUNCTION_1C_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1D_INITIAL
                CALL    EXTEND_FUNCTION_1D_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1E_INITIAL
                CALL    EXTEND_FUNCTION_1E_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1F_INITIAL
                CALL    EXTEND_FUNCTION_1F_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1G_INITIAL
                CALL    EXTEND_FUNCTION_1G_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1H_INITIAL
                CALL    EXTEND_FUNCTION_1H_INITIAL
                endif



                ifdef   EXTEND_FUNCTION_2A_INITIAL
                CALL    EXTEND_FUNCTION_2A_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2B_INITIAL
                CALL    EXTEND_FUNCTION_2B_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2C_INITIAL
                CALL    EXTEND_FUNCTION_2C_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2D_INITIAL
                CALL    EXTEND_FUNCTION_2D_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2E_INITIAL
                CALL    EXTEND_FUNCTION_2E_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2F_INITIAL
                CALL    EXTEND_FUNCTION_2F_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2G_INITIAL
                CALL    EXTEND_FUNCTION_2G_INITIAL
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2H_INITIAL
                CALL    EXTEND_FUNCTION_2H_INITIAL
                endif


                ;;-----------------------
MAIN_LOOP:      ;;- MAIN PROGRAM LOOP ---
                ;;-----------------------
                CLR     WDT
                CLR     WDT1
                CLR     WDT2

                ;----------------
                ;-CHECK POR ID --
                ;----------------
                MOV     A,042H
                XORM    A,POR_ID[0]
                MOV     A,053H
                SZ      Z
                XORM    A,POR_ID[1]
                SNZ     Z
                JMP     000H

                ;----------------------
                ;-RE INITIAL SYS. CLOCK
                ;----------------------  
                RELOAD_SYS_CLOCK

                ifdef   EXTEND_FUNCTION_1A
                CALL    EXTEND_FUNCTION_1A
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1B
                CALL    EXTEND_FUNCTION_1B
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1C
                CALL    EXTEND_FUNCTION_1C
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1D
                CALL    EXTEND_FUNCTION_1D
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1E
                CALL    EXTEND_FUNCTION_1E
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1F
                CALL    EXTEND_FUNCTION_1F
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1G
                CALL    EXTEND_FUNCTION_1G
                endif
                ;--
                ifdef   EXTEND_FUNCTION_1H
                CALL    EXTEND_FUNCTION_1H
                endif




                ifdef   EXTEND_FUNCTION_2A
                CALL    EXTEND_FUNCTION_2A
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2B
                CALL    EXTEND_FUNCTION_2B
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2C
                CALL    EXTEND_FUNCTION_2C
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2D
                CALL    EXTEND_FUNCTION_2D
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2E
                CALL    EXTEND_FUNCTION_2E
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2F
                CALL    EXTEND_FUNCTION_2F
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2G
                CALL    EXTEND_FUNCTION_2G
                endif
                ;--
                ifdef   EXTEND_FUNCTION_2H
                CALL    EXTEND_FUNCTION_2H
                endif


                ;----------------
                ;-SET POR ID  ---
                ;----------------
                MOV     A,042H      ;ASCII = B
                MOV     POR_ID[0],A
                MOV     A,053H      ;ASCII = S
                MOV     POR_ID[1],A

                ;--------------------
WDT_WAKEUP:     ;-WDT WAKEUP FUNCTION
                ;--------------------
                if      PowerSave==1
                CALL    _CHECK_KEY_WAKEUP
                endif


                JMP     MAIN_LOOP        
                




    


                                                                                                                                                
;;***********************************************************                           
;;*SUB. NAME:                                               *                           
;;*INPUT    :                                               *                           
;;*OUTPUT   :                                               *                           
;;*USED REG.:                                               *                           
;;*FUNCTION :                                               *                           
;;***********************************************************
CLEAR_RAM:
                MOV     MP1,A
            ifdef  BP
                ;-CHECK BANK
                SZ      BP
                JMP     $+7
            endif   
                ;-CHECK POR_ID RAM
                MOV     A,OFFSET POR_ID
                XOR     A,MP1
                MOV     A,OFFSET POR_ID+1
                SNZ     Z
                XOR     A,MP1
                SNZ     Z
                ;-CLEAR RAM 
                CLR     IAR1
                SIZA    MP1
                JMP     CLEAR_RAM
                      
                RET

                                                                                                                                                
;;***********************************************************                                                                                   
;;*SUB. NAME:                                               *                                                                                   
;;*INPUT    :                                               *                                                                                   
;;*OUTPUT   :                                               *                                                                                   
;;*USED REG.:                                               *                                                                                   
;;*FUNCTION :                                               *                                                                                   
;;***********************************************************                                                                                   
_LOAD_TKS_GLOBE_VARIES:  
_LOAD_HXT_REFERENCE:
                ;------------------------                                         
                ;-SET TKS LIBRARY OPTION-
                ;------------------------                                                  
                MOV     A,GlobeOptionA                                                                          
                MOV     _GLOBE_VARIES[0],A                                                                      
                MOV     A,GlobeOptionB                                                                          
                MOV     _GLOBE_VARIES[1],A                                                                      
                MOV     A,GlobeOptionC                                                                          
                MOV     _GLOBE_VARIES[2],A  

                ;--------------------------
                ;-SET TOUCH OR IO ATTRIBUTE
                ;--------------------------
                MOV     A,IO_TOUCH_ATTR&0FFH
                MOV     _KEY_IO_SEL[0],A
                ;-IF OVER 2 TOUCH IP (8~16KEY)
                if      TouchIPamount > 2
                MOV     A,(IO_TOUCH_ATTR>>8)&0FFH
                MOV     _KEY_IO_SEL[1],A
                endif
                ;-IF OVER 4 TOUCH IP (17~24KEY)
                if      TouchIPamount > 4 
                MOV     A,(IO_TOUCH_ATTR>>16)&0FFH
                MOV     _KEY_IO_SEL[2],A
                endif
                ;-IF OVER 6 TOUCH IP (25~32KEY)
                if      TouchIPamount > 6 
                MOV     A,(IO_TOUCH_ATTR>>24)&0FFH
                MOV     _KEY_IO_SEL[3],A
                endif

                ;------------------------
                ;-SET TOUCH KEY THRESHOLD
                ;------------------------
                ;-KEY1 THRESHOLD                                                                                
                MOV     A,Key1Threshold                                                                         
                MOV     _GLOBE_VARIES[3],A                                                                      
                ;-KEY2 THRESHOLD                                                                                
                MOV     A,Key2Threshold                                                                         
                MOV     _GLOBE_VARIES[4],A                                                                      
                ;-KEY3 THRESHOLD                                                                                
                MOV     A,Key3Threshold                                                                         
                MOV     _GLOBE_VARIES[5],A                                                                      
                ;-KEY4 THRESHOLD                                                                                
                MOV     A,Key4Threshold                                                                         
                MOV     _GLOBE_VARIES[6],A

                ;-IF OVER 1 TOUCH IP (5~8KEY)
                if      TouchIPamount > 1
                ;-KEY5 THRESHOLD                                                                                
                MOV     A,Key5Threshold                                                                         
                MOV     _GLOBE_VARIES[7],A                                                                      
                ;-KEY6 THRESHOLD                                                                                
                MOV     A,Key6Threshold                                                                         
                MOV     _GLOBE_VARIES[8],A                                                                      
                ;-KEY7 THRESHOLD                                                                                
                MOV     A,Key7Threshold                                                                         
                MOV     _GLOBE_VARIES[9],A                                                                      
                ;-KEY8 THRESHOLD                                                                                
                MOV     A,Key8Threshold                                                                         
                MOV     _GLOBE_VARIES[10],A
                endif

                ;-IF OVER 2 TOUCH IP (9~12KEY)
                if     TouchIPamount > 2
                ;-KEY9 THRESHOLD                                                                                
                MOV     A,Key9Threshold                                                                         
                MOV     _GLOBE_VARIES[11],A
                ;-KEY10 THRESHOLD                                                                                
                MOV     A,Key10Threshold                                                                         
                MOV     _GLOBE_VARIES[12],A
                ;-KEY11 THRESHOLD                                                                                
                MOV     A,Key11Threshold                                                                         
                MOV     _GLOBE_VARIES[13],A
                ;-KEY12 THRESHOLD                                                                                
                MOV     A,Key12Threshold                                                                         
                MOV     _GLOBE_VARIES[14],A
                endif

                ;-IF OVER 3 TOUCH IP (13~16KEY)
                if      TouchIPamount > 3
                ;-KEY13 THRESHOLD                                                                                
                MOV     A,Key13Threshold                                                                         
                MOV     _GLOBE_VARIES[15],A
                ;-KEY14 THRESHOLD                                                                                
                MOV     A,Key14Threshold                                                                         
                MOV     _GLOBE_VARIES[16],A
                ;-KEY15 THRESHOLD                                                                                
                MOV     A,Key15Threshold                                                                         
                MOV     _GLOBE_VARIES[17],A
                ;-KEY16 THRESHOLD                                                                                
                MOV     A,Key16Threshold                                                                         
                MOV     _GLOBE_VARIES[18],A
                endif

                ;-IF OVER 4 TOUCH IP (16~20KEY)
                if      TouchIPamount > 4
                ;-KEY17 THRESHOLD                                                                                
                MOV     A,Key17Threshold                                                                         
                MOV     _GLOBE_VARIES[19],A
                ;-KEY18 THRESHOLD                                                                                
                MOV     A,Key18Threshold                                                                         
                MOV     _GLOBE_VARIES[20],A
                ;-KEY19 THRESHOLD                                                                                
                MOV     A,Key19Threshold                                                                         
                MOV     _GLOBE_VARIES[21],A
                ;-KEY20 THRESHOLD                                                                                
                MOV     A,Key20Threshold                                                                         
                MOV     _GLOBE_VARIES[22],A
                endif

                ;-IF OVER 5 TOUCH IP (21~24KEY)
                if      TouchIPamount > 5
                ;-KEY17 THRESHOLD                                                                                
                MOV     A,Key21Threshold                                                                         
                MOV     _GLOBE_VARIES[23],A
                ;-KEY18 THRESHOLD                                                                                
                MOV     A,Key22Threshold                                                                         
                MOV     _GLOBE_VARIES[24],A
                ;-KEY19 THRESHOLD                                                                                
                MOV     A,Key23Threshold                                                                         
                MOV     _GLOBE_VARIES[25],A
                ;-KEY20 THRESHOLD                                                                                
                MOV     A,Key24Threshold                                                                         
                MOV     _GLOBE_VARIES[26],A
                endif

                ;-IF OVER 6 TOUCH IP (24~28KEY)
                if      TouchIPamount > 6
                ;-KEY17 THRESHOLD                                                                                
                MOV     A,Key25Threshold                                                                         
                MOV     _GLOBE_VARIES[27],A
                ;-KEY18 THRESHOLD                                                                                
                MOV     A,Key26Threshold                                                                         
                MOV     _GLOBE_VARIES[28],A
                ;-KEY19 THRESHOLD                                                                                
                MOV     A,Key27Threshold                                                                         
                MOV     _GLOBE_VARIES[29],A
                ;-KEY20 THRESHOLD                                                                                
                MOV     A,Key28Threshold                                                                         
                MOV     _GLOBE_VARIES[30],A
                endif

                ;-IF OVER 7 TOUCH IP (29~32KEY)
                if    TouchIPamount > 7
                ;-KEY17 THRESHOLD                                                                                
                MOV     A,Key29Threshold                                                                         
                MOV     _GLOBE_VARIES[31],A
                ;-KEY18 THRESHOLD                                                                                
                MOV     A,Key30Threshold                                                                         
                MOV     _GLOBE_VARIES[32],A
                ;-KEY19 THRESHOLD                                                                                
                MOV     A,Key31Threshold                                                                         
                MOV     _GLOBE_VARIES[33],A
                ;-KEY20 THRESHOLD                                                                                
                MOV     A,Key32Threshold                                                                         
                MOV     _GLOBE_VARIES[34],A
                endif


                RET



                                                      
                END
                


