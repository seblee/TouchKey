#define _CCV3_  // 定义C编译器版本.. --CCG 注释

#include "..\TKS_GLOBE_VARIES.H"
#include "..\MAIN_PROGRAM_V100\MAIN_PROGRAM_V100.H"

#include "user_type.h"

#define uchar unsigned char
#define uint unsigned int
/*****key**************************/
volatile _TKS_FLAGA_type keyTrg[2];
volatile uchar k_count[2];

#define KEY1 keyTrg[0].bits.b2
#define KEY2 keyTrg[0].bits.b3
#define KEY3 keyTrg[0].bits.b1

#define KEY1Restain keyTrg[1].bits.b2
#define KEY2Restain keyTrg[1].bits.b3
#define KEY3Restain keyTrg[1].bits.b1

#define keyNUM 4
#define RESTAIN_TIMES 200  // 200 × 10ms = 2s
uchar keyTime[keyNUM] = {0};
/*****beep**************************/
#define BEEP _pc0

/*****led**************************/
#define LED1 _pc4
#define LED2 _pc5
#define LED3 _pc6
#define LED4 _pc7
#define LED5 _pb3
#define LED6 _pb4
#define LED7 _pb5
#define LED8 _pb6

_USR_FLAGA_type ledState1;
_USR_FLAGA_type ledState2;
#define led1State ledState1.sbits.s0
#define led2State ledState1.sbits.s1
#define led3State ledState1.sbits.s2
#define led4State ledState1.sbits.s3
#define led5State ledState2.sbits.s0
#define led6State ledState2.sbits.s1
#define led7State ledState2.sbits.s2
#define led8State ledState2.sbits.s3

#define KEY4 _pb7

volatile _TKS_FLAGA_type bitFlag;

#define beepFlag bitFlag.bits.b0
#define rxFlag bitFlag.bits.b1
#define txFlag bitFlag.bits.b2
#define recOK bitFlag.bits.b3
#define flashFlag bitFlag.bits.b4

uchar rxBuff;
uchar rxCount    = 0;
uchar rxData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0a};
uchar txBuff[10] = {0};
uchar txCount    = 0;

void receiveUart(uchar data)
{
    // static uchar dataNum;
    if ((rxCount == 0) && (data == 0xa5))
    {
        rxData[rxCount] = data;
        rxCount++;
    }
    else if ((rxCount == 1) && (data == 0x53))
    {
        rxData[rxCount] = data;
        //   dataNum         = rxData[rxCount] & 0x0f;
        rxCount++;
    }
    else if (rxCount == 2)
    {
        rxData[rxCount] = data;
        rxCount++;
    }
    else if (rxCount == 3)
    {
        rxData[rxCount] = data;
        rxCount++;
    }
    else if (rxCount == 4)
    {
        rxData[rxCount] = data;
        rxCount++;
    }
    else
    {
        rxCount = 0;
    }

    if (rxCount == 5)
    {
        rxCount = 0;
        recOK   = 1;
    }
}

//==============================================
//**********************************************
//==============================================
//#pragma vector  Interrupt_Extemal        @ 0x04
// void Interrupt_Extemal()

void __attribute((interrupt(0x04))) Interrupt_Extemal(void)
{
    GCC_NOP();
}

//==============================================
//**********************************************
// CTM0 CCRP INTERRUPT
//==============================================
//#pragma vector  Interrupt_CTM0_CCRP        @ 0x10
// void Interrupt_CTM0_CCRP()

void __attribute((interrupt(0x10))) Interrupt_CTM0_CCRP(void)
{
    GCC_NOP();
}

//==============================================
//**********************************************
// CTM0 CCRA INTERRUPT
// 250uS---��ʱ��
//==============================================
//#pragma vector  Interrupt_CTM0_CCRA       @ 0x14
// void Interrupt_CTM0_CCRA()
void __attribute((interrupt(0x14))) Interrupt_CTM0_CCRA(void)
{
    GCC_CLRWDT();  //_clrwdt();
}

//==============================================
//**********************************************
// PTM1 CCRP INTERRUPT
//==============================================
//#pragma vector  Interrupt_PTM1_CCRP       @ 0x18
// void Interrupt_PTM1_CCRP()

void __attribute((interrupt(0x18))) Interrupt_PTM1_CCRP(void)
{
    GCC_NOP();  //_nop();
}

//==============================================
//**********************************************
// PTM1 CCRA INTERRUPT
//==============================================
//#pragma vector  Interrupt_PTM1_CCRA        @ 0x1C
// void Interrupt_PTM1_CCRA()

void __attribute((interrupt(0x1c))) Interrupt_PTM1_CCRA(void)
{
}
//==============================================
//**********************************************
// TB1 INTERRUPT
//==============================================
//#pragma vector  Interrupt_TB1      @ 0x20
// void Interrupt_TB1()

void __attribute((interrupt(0x20))) Interrupt_TB1(void)
{
    // LED5 = !LED5;
    GCC_NOP();  //_nop();
}
//==============================================
//**********************************************
// TB1 INTERRUPT
//==============================================
//#pragma vector  Interrupt_TB1      @ 0x20
// void Interrupt_TB1()

void __attribute((interrupt(0x2c))) Interrupt_UART(void)
{
    if (_rxif)
    {
        rxBuff = _txr_rxr;
        receiveUart(rxBuff);
    }
}
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{
    // _pac  = 0b11111111;
    // _papu = 0b11111111;
    // _pa   = 0b11111111;

    _lvdc = 0x00;

    _sledc0 = 0xff;
    _sledc1 = 0xff;

    _eea = 0x00;
    _eed = 0x00;

    _i2ctoc = 0x00;
    _iicc0  = 0x00;
    _iicc1  = 0x00;
    _iicd   = 0x00;
    _iica   = 0x00;

    _tmpc = 0x00;

    _ctrl = 0x00;

    _tbc |= 0xf0;
    _intc2 |= 0x01;

    /******Data****************/
    beepFlag = 1;
}

//==============================================
//**********************************************
//==============================================

void USER_PROGRAM()
{
    uchar i;
    uchar keyRestain = 0;
    if (TKS_63MSF)
    {
        if (beepFlag)
        {
            BEEP     = 1;
            beepFlag = 0;
        }
        else
            BEEP = 0;
    }

    if (SCAN_CYCLEF)
    {
        GET_KEY_BITMAP();
        keyTrg[0].byte = DATA_BUF[1] & (DATA_BUF[1] ^ k_count[0]);
        k_count[0]     = DATA_BUF[1];
        if (keyTrg[0].byte)
        {
            beepFlag = 1;
        }

        for (i = 0; i < keyNUM; i++)
        {
            if (k_count[0] & (1 << i))
            {
                if (keyTime[i] < RESTAIN_TIMES)
                    keyTime[i]++;
                else
                    keyRestain |= (1 << i);
            }
            else
            {
                // if (keyTime[i] > 0)  // short press
                //     Key_Up_Trg |= (1 << i);
                // else
                //     Key_Up_Trg &= (~(1 << i));

                keyTime[i] = 0;
                keyRestain &= (~(1 << i));
            }
        }
        keyTrg[1].byte = keyRestain & (keyRestain ^ k_count[1]);
        k_count[1]     = keyRestain;
        if (keyTrg[1].byte)
        {
            beepFlag = 1;
        }
    }
}

void USER_UART_INITIAL()
{
    /********uart**************/
    _usr   = 0x00;
    _ucr1  = 0x80;
    _ucr2  = 0xe4;
    _brg   = 0x19;
    _uarte = 1;
}

void USER_UART()
{
    uchar i;
    if (recOK)
    {
        ledState1.byte = rxData[2];
        ledState2.byte = rxData[3];
        recOK          = 0;
    }
    /********数据发送*********/
    if (TKS_63MSF)
    {
        txCount = 4;
    }
    if (txCount /*&& _txif*/)
    {
        if (txCount == 4)
        {
            txBuff[3] = 0xa5;
            txBuff[2] = 0x52;
            txBuff[1] = k_count[0];
            txBuff[0] = k_count[1];
        }
        for (i = 0; i < txCount; i++)
        {
            if (_txif)
            {
                _txr_rxr = txBuff[txCount - 1 - i];
                txCount--;
            }
            else
            {
                break;
            }
        }
        // txCount = 0;
        // if (txCount == 4)
        // {
        //     _txr_rxr = 0xa5;
        // }
        // else if (txCount == 3)
        // {
        //     _txr_rxr = 0x52;
        // }
        // else if (txCount == 2)
        // {
        //     _txr_rxr = k_count[0];
        // }
        // else if (txCount == 1)
        // {
        //     _txr_rxr = k_count[1];
        // }
        // else
        // {
        //     txCount = 0;
        // }
        // txCount--;
    }
}
void USER_LED_INITIAL()
{
    /********LED**************/
    _pbc  = 0b10000000;
    _pbpu = 0b10000000;
    _pb   = 0b00000000;

    _pcc  = 0b00001110;
    _pcpu = 0b00000000;
    _pc   = 0b00000000;
}

void USER_LED()
{
    if (TKS_500MSF)
    {
        if (flashFlag)
        {
            flashFlag = 0;
        }
        else
        {
            flashFlag = 1;
        }

        if (led1State == 0)
        {
            LED1 = 1;
        }
        if (led2State == 0)
        {
            LED2 = 1;
        }
        if (led3State == 0)
        {
            LED3 = 1;
        }
        if (led4State == 0)
        {
            LED4 = 1;
        }
        if (led5State == 0)
        {
            LED5 = 1;
        }
        if (led6State == 0)
        {
            LED6 = 1;
        }
        if (led7State == 0)
        {
            LED7 = 1;
        }
        if (led8State == 0)
        {
            LED8 = 1;
        }

        if (led1State == 1)
        {
            LED1 = 0;
        }
        if (led2State == 1)
        {
            LED2 = 0;
        }
        if (led3State == 1)
        {
            LED3 = 0;
        }
        if (led4State == 1)
        {
            LED4 = 0;
        }
        if (led5State == 1)
        {
            LED5 = 0;
        }
        if (led6State == 1)
        {
            LED6 = 0;
        }
        if (led7State == 1)
        {
            LED7 = 0;
        }
        if (led8State == 1)
        {
            LED8 = 0;
        }

        if (led1State == 2)
        {
            LED1 = flashFlag;
        }
        if (led2State == 2)
        {
            LED2 = flashFlag;
        }
        if (led3State == 2)
        {
            LED3 = flashFlag;
        }
        if (led4State == 2)
        {
            LED4 = flashFlag;
        }
        if (led5State == 2)
        {
            LED5 = flashFlag;
        }
        if (led6State == 2)
        {
            LED6 = flashFlag;
        }
        if (led7State == 2)
        {
            LED7 = flashFlag;
        }
        if (led8State == 2)
        {
            LED8 = flashFlag;
        }
    }
}