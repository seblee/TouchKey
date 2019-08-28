#include "LIBV413_IIC_SLAVE_TEST_V100.H"



#define IIC_ADDRESS 0xA0
#define IIC_RW_RAM_Size 8

//*******************************************************************
#define CMD_R_Lib_VersionL  0x00
#define CMD_R_Lib_VersionH  0x01
#define CMD_R_KeyAmount 0x02
#define CMD_R_EE_Status 0x03
#define CMD_R_TK_Select0    0x04
#define CMD_R_TK_Select1    CMD_R_TK_Select0+1
#define CMD_R_TK_Select2    CMD_R_TK_Select0+2
#define CMD_R_TK_Select3    CMD_R_TK_Select0+3
#define CMD_R_KeyStatus0    0x08
#define CMD_R_KeyStatus1    CMD_R_KeyStatus0+1
#define CMD_R_KeyStatus2    CMD_R_KeyStatus0+2
#define CMD_R_KeyStatus3    CMD_R_KeyStatus0+3
#define CMD_R_K1_Freq   0x010
#define CMD_R_K1_Ref    0x050
#define CMD_R_K1_Offset 0x090
#define CMD_R_K1_RCC    0x0B0

#define CMD_RW_Global   0x0D0
#define CMD_RW_DeviceA  CMD_RW_Global+0
#define CMD_RW_DeviceB  CMD_RW_Global+1
#define CMD_RW_KeyAmount    CMD_RW_Global+2
#define CMD_RW_OptionA  CMD_RW_Global+3
#define CMD_RW_OptionB  CMD_RW_Global+4
#define CMD_RW_OptionC  CMD_RW_Global+5
//#define   CMD_RW_     CMD_RW_Global+6
//#define   CMD_RW_     CMD_RW_Global+7
#define CMD_RW_K1_TH    CMD_RW_Global+8
//*********************************************************************




void IIC_Msg(){
    #asm
        message 'IIC Slave Mode'
    #endasm
}



/*******************************************************************/
#pragma rambank 0

bit bWrite1st;
unsigned char IIC_Data[3];

unsigned char IIC_R_RAM[4];
unsigned char IIC_RW_RAM[IIC_RW_RAM_Size];
unsigned char IIC_CheckSUM;



#ifdef  _BS82C16A_
        #define _haas   _iichaas
        #define _htx    _iichtx
        #define _txak   _iictxak
        #define _rxak   _iicrxak
        #define _srw    _iicsrw
        #define _simd   _iicd
        #define _sima   _iica
        #define _sime   _iice
        #define _simen  _iicen
        #define _simf   _iicf
        #define IICINTaddress   0x24
#endif

#ifdef  _BS82D20A_
        #define _haas   _iichaas
        #define _htx    _iichtx
        #define _txak   _iictxak
        #define _rxak   _iicrxak
        #define _srw    _iicsrw
        #define _simd   _iicd
        #define _sima   _iica
        #define _sime   _iice
        #define _simen  _iicen
        #define _simf   _iicf
        #define IICINTaddress   0x24
#endif


#ifdef  _BS83B08A_
        #define IICINTaddress   0x10
#endif

#ifdef  _BS83B12A_
        #define IICINTaddress   0x10
#endif

#ifdef  _BS83B16A_
        #define IICINTaddress   0x10
#endif

#ifdef  _BS84B08A_
        #define IICINTaddress   0x10
#endif

#ifdef  _BS84C12A_
        #define IICINTaddress   0x10
#endif



#define Out 0
#define In 1
#define Index 2


#define Dummy_Read  _acc=_simd 
#define AddrMatch   _haas
#define MasterRead  _srw

#define SlaveMode   _htx
#define SlaveTxMode SlaveMode=1
#define SlaveRxMode SlaveMode=0

#define SlaveSendACK _txak=0

#define SlaveRecAck _rxak   //0:Slave receive acknowledge flag
                //1:Slave do not receive acknowledge flag





void LIBV413_IIC_SLAVE_TEST_V100_INITIAL(){


    //_pac0=1;          //SDA input
    //_pac2=1;          //SCL input

    _papu0=1;
    _papu2=1;


    GET_LIB_VER();
    IIC_R_RAM[0]=DATA_BUF[0];
    IIC_R_RAM[1]=DATA_BUF[1];
    GET_KEY_AMOUNT();
    IIC_R_RAM[2]=_acc;

    IIC_RW_RAM[0]=0;
    IIC_RW_RAM[1]=0;
    IIC_RW_RAM[2]=IIC_R_RAM[2];
    IIC_RW_RAM[3]=GLOBE_VARIES[0];
    IIC_RW_RAM[4]=GLOBE_VARIES[1];
    IIC_RW_RAM[5]=GLOBE_VARIES[2];
    IIC_RW_RAM[6]=0;
    IIC_RW_RAM[7]=0;
}

void LIBV413_IIC_SLAVE_TEST_V100(){
unsigned char i;
    if(TKS_ACTIVEF){
        _simen=1;
        _sime=1;
        _sima=IIC_ADDRESS;
        _i2ctoc=0b10111111;     //Enable I2C 1 Sec Time-out
    //---------------------------
    #ifdef  _BS83B08A_
        _simc0=0b11000010;    //I2C Mode ,Enable SIM
    #endif
    //---------------------------
    #ifdef  _BS83B12A_
        _simc0=0b11000010;    //I2C Mode ,Enable SIM
    #endif
    //---------------------------
    #ifdef  _BS83B16A_
        _simc0=0b11000010;    //I2C Mode ,Enable SIM
    #endif
    //---------------------------
    #ifdef  _BS84B08A_
        _simc0=0b11000010;    //I2C Mode ,Enable SIM
    #endif
    //---------------------------
    #ifdef  _BS84C12A_
        _simc0=0b11000010;    //I2C Mode ,Enable SIM
    #endif
    //---------------------------

        if(IIC_R_RAM[3]&0x04){
            IIC_R_RAM[3]&=0xfb;
            IIC_R_RAM[2]=IIC_RW_RAM[2];
            GLOBE_VARIES[0]=IIC_RW_RAM[3];
            GLOBE_VARIES[1]=IIC_RW_RAM[4];
            GLOBE_VARIES[2]=IIC_RW_RAM[5];

            LIBRARY_RESET();
            LIBV413_IIC_SLAVE_TEST_V100_INITIAL();
        }
        if(IIC_R_RAM[3]&0x80){
                
                //Compatible with old main_program.asm
                #asm
                        IFDEF _LOAD_TKS_GLOBE_VARIES
                CALL  _LOAD_TKS_GLOBE_VARIES
                ENDIF
                
                IFDEF _LOAD_HXT_REFERENCE
                CALL _LOAD_HXT_REFERENCE
                ENDIF
            #endasm
            
            LIBV413_IIC_SLAVE_TEST_V100_INITIAL();
        //---------------------------
        #ifdef  _BS83B08A_
            _simc0=0;                                         
        #endif
        //---------------------------
        #ifdef  _BS83B12A_
            _simc0=0;
        #endif
        //---------------------------
        #ifdef  _BS83B16A_
            _simc0=0;
        #endif
        //---------------------------
        #ifdef  _BS84B08A_
            _simc0=0;
        #endif
        //---------------------------
        #ifdef  _BS84C12A_
            _simc0=0;
        #endif
        //---------------------------
            _simen=0;
            _sime=0;
            _simf=0;
            LIBRARY_RESET();
        }
    }

}

#pragma vector SIM_INT @ IICINTaddress
void    SIM_INT(){
    _simf=0;
    if(AddrMatch){
        //1:address match
        if(MasterRead){
            /* -------------------------- */
            //1: master wants to read data,Slave device should be in transmit mode
            /* -------------------------- */
            SlaveTxMode;        //Slave device is the transmitter
            _simd=IIC_Data[Out];
            /* -------------------------- */
            goto NextData2OutBuf;
        }else{
            /* -------------------------- */
            //0:master wants to write data,Slave device should be in receive mode
            /* -------------------------- */
            SlaveRxMode;        //Slave device is the receiver
            SlaveSendACK;       //Slave send acknowledge
            Dummy_Read;     //DUMMY READ
            /* -------------------------- */
            bWrite1st=0;
        }
    }else{
        //0:read/write data
        if(SlaveMode){
            //1:Slave device is the transmitter
            //Master wants to read
            if(SlaveRecAck){
                /* -------------------------- */
                //1: Slave do not receive acknowledge
                SlaveRxMode;    //receive mode (master write)
                SlaveSendACK;   //enable transmits acknowledge
                Dummy_Read; //DUMMY READ
                /* -------------------------- */
            }else{
                /* -------------------------- */
                //0: Slave receive acknowledge
                _simd=IIC_Data[Out];
                /* -------------------------- */

                goto NextData2OutBuf;
            }
        }else{
            /* -------------------------- */
            //0: Slave device is the receiver
            //Master wants to write
            SlaveRxMode;        //receive mode (master write)
            SlaveSendACK;       //enable transmits acknowledge
            IIC_Data[In]=_simd;    //receive data
            /* -------------------------- */


            IIC_Data[Out]=0;
            if(bWrite1st){
                /****************************************/
                if((IIC_Data[Index]-0xd0)==(IIC_R_RAM[2]+8)){
                    if(IIC_R_RAM[3]&0x01){
                        IIC_R_RAM[3]&=0xfe;
                        if(IIC_Data[In]==IIC_CheckSUM) IIC_R_RAM[3]|=0b00000100;    //bWriteEE
                        else IIC_R_RAM[3]|=0x80;
                    }
                }else{
                    if(IIC_Data[Index]==CMD_RW_Global){
                        IIC_CheckSUM=0;
                        IIC_R_RAM[3]|=0x01;
                    }

                    if(IIC_R_RAM[3]&0x01){
                        if(IIC_Data[Index]<0xd8){
                            IIC_RW_RAM[(IIC_Data[Index]-0xd0)]=IIC_Data[In];
                        }else{
                            IIC_Data[Out]=(IIC_Data[Index]-0xd5);   //0xd8+3
                            GLOBE_VARIES[IIC_Data[Out]]=IIC_Data[In];
                        }
                        IIC_CheckSUM+=IIC_Data[In];
                        IIC_Data[Index]++;      //Next
                    }
                }
                /****************************************/
            }else{
                /****************************************/
                /*  start+device(addr)+w+DATA   */
                IIC_Data[Index]=IIC_Data[In];
                bWrite1st=1;
                /****************************************/
                goto PRERead;


                NextData2OutBuf:
                    IIC_Data[Index]++;      //Next
                PRERead:
                    IIC_Data[Out]=0;
                    if(IIC_Data[Index]<0x10){
                        switch(IIC_Data[Index]){
                            case 0:
                                IIC_Data[Out]=IIC_R_RAM[0];
                                break;
                            case 1:
                                IIC_Data[Out]=IIC_R_RAM[1];
                                break;
                            case 2:
                                IIC_Data[Out]=IIC_R_RAM[2];
                                break;
                            case 3:
                                IIC_Data[Out]=IIC_R_RAM[3];
                                break;
                            case 4:
                                IIC_Data[Out]=KEY_IO_SEL[0]^0xff;
                                break;
                            case 5:
                                IIC_Data[Out]=KEY_IO_SEL[1]^0xff;
                                break;
                            case 6:
                                IIC_Data[Out]=KEY_IO_SEL[2]^0xff;
                                break;
                            case 7:
                                IIC_Data[Out]=KEY_IO_SEL[3]^0xff;
                                break;

                            case 8:
                                IIC_Data[Out]=KEY_DATA[0];
                                break;
                            case 9:
                                IIC_Data[Out]=KEY_DATA[1];
                                break;
                            case 10:
                                IIC_Data[Out]=KEY_DATA[2];
                                break;
                            case 11:
                                IIC_Data[Out]=KEY_DATA[3];
                                break;
                        }
                        //IIC_Data[Out]=IIC_R_RAM[IIC_Data[Index]];


                    }else if(IIC_Data[Index]<0x50){ //0x10~0x4F (Key ENV)
                        if((IIC_Data[Index]&0b00000001)==0){

                            #asm
                                extern  _KEY_REF:BYTE ;FREQ:BYTE

                                mov a,_IIC_Data[Index]
                                sub a,010h
                                clr [0ah].0
                                rrc __acc
                                rl  __acc
                                rl  __acc

                                add a,OFFSET    _KEY_REF[0] ;_KEY_FREQ[0]
                                inc __acc
                                mov __mp1,a
                                mov a,bank  _KEY_REF[0];FREQ[0]
                                mov __bp,a

                                mov a,__iar1
                                mov _IIC_Data[Out],a
                              ; inc __mp1
                              ; mov a,__iar1
                              ; and a,0fh
                              ; mov _IIC_Data[In],a
                                clr _IIC_Data[In]  
                            #endasm
                        }else IIC_Data[Out]=IIC_Data[In];

                    }else if(IIC_Data[Index]<0x90){ //0x50~0x8f (Key REF)
                        if((IIC_Data[Index]&0b00000001)==0){

                            #asm
                               ;extern  _KEY_REF:BYTE
                                mov a,_IIC_Data[Index]
                                sub a,050h
                                clr [0ah].0
                                rrc __acc
                                rl  __acc
                                rl  __acc

                                add a,OFFSET    _KEY_REF[0]
                                mov __mp1,a
                                mov a,bank  _KEY_REF[0]
                                mov __bp,a

                                mov a,__iar1
                                mov _IIC_Data[Out],a
                              ; inc __mp1
                              ; mov a,__iar1
                              ; and a,0fh
                              ; mov _IIC_Data[In],a
                                clr _IIC_Data[In]  
                            #endasm
                        }else IIC_Data[Out]=IIC_Data[In];

                    }else if(IIC_Data[Index]<0xb0){ //0x90~0xaf (Key Offset)
                    }else if(IIC_Data[Index]<0xd0){ //0xb0~0xcf (Key RCC)

                        #asm
                               ;extern  _KEY_STATUS:BYTE
                            mov a,_IIC_Data[Index]
                            sub a,0b0h
                            rl  __acc
                            rl  __acc
                            add a,OFFSET   _KEY_REF[0]  
                            add a,3
                            mov __mp1,a
                            mov a,bank  _KEY_REF[0]
                            mov __bp,a

                            mov a,__iar1
                            mov _IIC_Data[Out],a
                        #endasm

                        //IIC_Data[In]=(IIC_Data[Index]-0xb0);
                        //IIC_Data[Out]=BALANCE_CAP[IIC_Data[In]];
                    }else if(IIC_Data[Index]>=0xd8){

                        #asm
                            mov a,_IIC_Data[Index]
                            sub a,0d5h      //0d8+3
                            add a,OFFSET _GLOBE_VARIES
                            mov __mp1,a
                            mov a,BANK _GLOBE_VARIES
                            mov __bp,a
                            mov a,__iar1

                            mov _IIC_Data[Out],a
                        #endasm

                        //IIC_Data[In]=(IIC_Data[Index]-0xd8)+3;
                        //IIC_Data[Out]=GLOBE_VARIES[IIC_Data[In]];
                    }else if(IIC_Data[Index]>=0xd0){    // 0xd0~0xff
                        #asm
                            mov a,_IIC_Data[Index]
                            sub a,0d0h
                            add a,OFFSET _IIC_RW_RAM
                            mov __mp1,a
                            mov a,BANK _IIC_RW_RAM
                            mov __bp,a
                            mov a,__iar1

                            mov _IIC_Data[Out],a
                        #endasm

                        //IIC_Data[Out]=IIC_RW_RAM[(IIC_Data[Index]-0xd0)];
                    }
                /****************************************/
            }
        }
    }



}
/*******************************************************************/




