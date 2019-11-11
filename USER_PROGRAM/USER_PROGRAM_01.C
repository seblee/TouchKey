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
#define KEY4 keyTrg[0].bits.b0

#define KEY1Restain keyTrg[1].bits.b2
#define KEY2Restain keyTrg[1].bits.b3
#define KEY3Restain keyTrg[1].bits.b1
#define KEY4Restain keyTrg[1].bits.b0

#define keyNUM 4
#define RESTAIN_TIMES 200  // 200 × 10ms = 2s
uchar keyTime[keyNUM] = {0};
uchar keyData         = 0;
#define _pin_Pb7 _pb7
#define T_S _pb0
/*****beep**************************/
#define BEEP _pc0
uchar beepCount = 1;
/*****led**************************/
#define LED1 _pc4
#define LED2 _pc5
#define LED3 _pc6
#define LED4 _pc7
#define LED5 _pb3
#define LED6 _pb4
#define LED7 _pb5
#define LED8 _pb6

_USR_FLAGA_type ledState[5];
#define led1State ledState[0].s4bits.s0
#define led2State ledState[0].s4bits.s1
#define led3State ledState[1].s4bits.s0
#define led4State ledState[1].s4bits.s1
#define led5State ledState[2].s4bits.s0
#define led6State ledState[2].s4bits.s1
#define led7State ledState[3].s4bits.s0
#define led8State ledState[3].s4bits.s1
#define led9State ledState[4].s4bits.s0

volatile _TKS_FLAGA_type bitFlag;

#define beepFlag bitFlag.bits.b0
#define beepON bitFlag.bits.b1
#define beepOFF bitFlag.bits.b2
#define recOK bitFlag.bits.b3
#define flashFlag_0_5HZ bitFlag.bits.b4
#define flashFlag_1HZ bitFlag.bits.b5
#define flashFlag_2HZ bitFlag.bits.b6
#define b_pin_Pb7 bitFlag.bits.b7

uchar rxBuff;
uchar rxCount    = 0;
uchar rxData[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0x0a};
uchar txBuff[10] = {0};
uchar txCount    = 0;

void receiveUart(uchar data)
{
    static uchar checkSum, ucount;
    if ((rxCount == 0) && (data == 0xa7))
    {
        rxData[rxCount] = data;
        checkSum        = data;
        rxCount++;
    }
    else if ((rxCount == 1) && ((data & 0xf0) == 0xf0))
    {
        rxData[rxCount] = data;
        checkSum += data;
        rxCount++;
        ucount = data & 0x0f;
    }
    else if (rxCount >= 2)
    {
        if (ucount > 0)
        {
            rxData[rxCount] = data;
            checkSum += data;
            rxCount++;
            ucount--;
        }
        else if ((ucount == 0) && (checkSum == data))
        {
            rxCount  = 0;
            recOK    = 1;
            checkSum = 0;
        }
        else
        {
            rxCount = 0;
        }
    }
    else
    {
        rxCount = 0;
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
    beepCount = 1;
    // BEEP     = 1;
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
        if (beepON)
        {
            beepFlag  = 1;
            BEEP      = 1;
            beepCount = 0;
        }
        else
        {
            if (beepFlag)
            {
                beepFlag = 0;
                BEEP     = 0;
            }
            else if (beepCount)
            {
                beepCount--;
                beepFlag = 1;
                BEEP     = 1;
            }
        }
    }

    if (SCAN_CYCLEF)
    {
        GET_KEY_BITMAP();
        // keyData = DATA_BUF[1];

        if (T_S)
        {
            keyData &= 0xf8;
            keyData |= DATA_BUF[1] & 0xf2;
            keyData |= ((DATA_BUF[1] >> 2) & 0x01);

            if (_pin_Pb7 == b_pin_Pb7)
            {
                if (b_pin_Pb7)
                    keyData &= 0xf7;
                else
                {
                    keyData |= 0x08;
                }
            }
            else
            {
                b_pin_Pb7 = _pin_Pb7;
            }
        }
        else
        {
            keyData = DATA_BUF[1];
        }

        keyTrg[0].byte = keyData & (keyData ^ k_count[0]);
        k_count[0]     = keyData;

        if (keyTrg[0].byte)
        {
            beepCount++;
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
            beepCount++;
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
    // uchar i;
    if (recOK)
    {
        ledState[0].byte = rxData[2];
        ledState[1].byte = rxData[3];
        ledState[2].byte = rxData[4];
        ledState[3].byte = rxData[5];
        ledState[4].byte = rxData[6];
        beepON           = ((rxData[7] & 0xf0) > 0);
        beepCount += rxData[7] & 0x0f;
        recOK = 0;
        if (txCount == 0)
            txCount = 5;
    }
    /********数据发送*********/
    if (TKS_63MSF)
    {
        // txCount = 5;
    }
    if (txCount && _txif)
    {
        if (txCount == 5)
        {
            txBuff[0] = 0xa7;
            txBuff[1] = 0xf2;
            txBuff[2] = k_count[0];
            txBuff[3] = k_count[1];
            txBuff[4] = 0;
            txBuff[4] += txBuff[0];
            txBuff[4] += txBuff[1];
            txBuff[4] += txBuff[2];
            txBuff[4] += txBuff[3];
        }

        _txr_rxr = txBuff[5 - txCount];
        txCount--;
    }
}
void USER_LED_INITIAL()
{
    /******KEY**LED**************/
    _pbc  = 0b10000001;
    _pbpu = 0b10000001;
    _pb   = 0b10000001;

    _pcc  = 0b00001110;
    _pcpu = 0b00000000;
    _pc   = 0b00000000;

    LED1 = LED_ON;
    LED2 = LED_ON;
    LED3 = LED_ON;
    LED4 = LED_ON;
    LED5 = LED_ON;
    LED6 = LED_ON;
    LED7 = LED_ON;
    LED8 = LED_ON;
}

void USER_LED()
{
    {
        if (led1State == STATE_LED_OFF)
        {
            LED1 = LED_OFF;
        }
        if (led2State == STATE_LED_OFF)
        {
            LED2 = LED_OFF;
        }
        if (led3State == STATE_LED_OFF)
        {
            LED3 = LED_OFF;
        }
        if (led4State == STATE_LED_OFF)
        {
            LED4 = LED_OFF;
        }
        if (T_S)
        {
            if (led9State == STATE_LED_OFF)
            {
                LED5 = LED_OFF;
            }
        }
        else
        {
            if (led5State == STATE_LED_OFF)
            {
                LED5 = LED_OFF;
            }
        }
        if (led6State == STATE_LED_OFF)
        {
            LED6 = LED_OFF;
        }
        if (led7State == STATE_LED_OFF)
        {
            LED7 = LED_OFF;
        }
        if (led8State == STATE_LED_OFF)
        {
            LED8 = LED_OFF;
        }

        if (led1State == STATE_LED_ON)
        {
            LED1 = LED_ON;
        }
        if (led2State == STATE_LED_ON)
        {
            LED2 = LED_ON;
        }
        if (led3State == STATE_LED_ON)
        {
            LED3 = LED_ON;
        }
        if (led4State == STATE_LED_ON)
        {
            LED4 = LED_ON;
        }
        if (T_S)
        {
            if (led9State == STATE_LED_ON)
            {
                LED5 = LED_ON;
            }
        }
        else
        {
            if (led5State == STATE_LED_ON)
            {
                LED5 = LED_ON;
            }
        }
        if (led6State == STATE_LED_ON)
        {
            LED6 = LED_ON;
        }
        if (led7State == STATE_LED_ON)
        {
            LED7 = LED_ON;
        }
        if (led8State == STATE_LED_ON)
        {
            LED8 = LED_ON;
        }
    }

    if (TKS_250MSF)
    {
        if (flashFlag_2HZ)
        {
            flashFlag_2HZ = 0;
        }
        else
        {
            flashFlag_2HZ = 1;
        }
        if (led1State == STATE_LED_FLASH_2HZ)
        {
            LED1 = flashFlag_2HZ;
        }
        if (led2State == STATE_LED_FLASH_2HZ)
        {
            LED2 = flashFlag_2HZ;
        }
        if (led3State == STATE_LED_FLASH_2HZ)
        {
            LED3 = flashFlag_2HZ;
        }
        if (led4State == STATE_LED_FLASH_2HZ)
        {
            LED4 = flashFlag_2HZ;
        }
        if (T_S)
        {
            if (led9State == STATE_LED_FLASH_2HZ)
            {
                LED5 = flashFlag_2HZ;
            }
        }
        else
        {
            if (led5State == STATE_LED_FLASH_2HZ)
            {
                LED5 = flashFlag_2HZ;
            }
        }
        if (led6State == STATE_LED_FLASH_2HZ)
        {
            LED6 = flashFlag_2HZ;
        }
        if (led7State == STATE_LED_FLASH_2HZ)
        {
            LED7 = flashFlag_2HZ;
        }
        if (led8State == STATE_LED_FLASH_2HZ)
        {
            LED8 = flashFlag_2HZ;
        }
    }

    if (TKS_500MSF)
    {
        if (flashFlag_1HZ)
        {
            flashFlag_1HZ = 0;
        }
        else
        {
            flashFlag_1HZ = 1;
        }
        if (led1State == STATE_LED_FLASH_1HZ)
        {
            LED1 = flashFlag_1HZ;
        }
        if (led2State == STATE_LED_FLASH_1HZ)
        {
            LED2 = flashFlag_1HZ;
        }
        if (led3State == STATE_LED_FLASH_1HZ)
        {
            LED3 = flashFlag_1HZ;
        }
        if (led4State == STATE_LED_FLASH_1HZ)
        {
            LED4 = flashFlag_1HZ;
        }
        if (T_S)
        {
            if (led9State == STATE_LED_FLASH_1HZ)
            {
                LED5 = flashFlag_1HZ;
            }
        }
        else
        {
            if (led5State == STATE_LED_FLASH_1HZ)
            {
                LED5 = flashFlag_1HZ;
            }
        }
        if (led6State == STATE_LED_FLASH_1HZ)
        {
            LED6 = flashFlag_1HZ;
        }
        if (led7State == STATE_LED_FLASH_1HZ)
        {
            LED7 = flashFlag_1HZ;
        }
        if (led8State == STATE_LED_FLASH_1HZ)
        {
            LED8 = flashFlag_1HZ;
        }

        if (flashFlag_1HZ)
        {
            if (flashFlag_0_5HZ)
            {
                flashFlag_0_5HZ = 0;
            }
            else
            {
                flashFlag_0_5HZ = 1;
            }
            if (led1State == STATE_LED_FLASH_0_5HZ)
            {
                LED1 = flashFlag_0_5HZ;
            }
            if (led2State == STATE_LED_FLASH_0_5HZ)
            {
                LED2 = flashFlag_0_5HZ;
            }
            if (led3State == STATE_LED_FLASH_0_5HZ)
            {
                LED3 = flashFlag_0_5HZ;
            }
            if (led4State == STATE_LED_FLASH_0_5HZ)
            {
                LED4 = flashFlag_0_5HZ;
            }
            if (T_S)
            {
                if (led9State == STATE_LED_FLASH_0_5HZ)
                {
                    LED5 = flashFlag_0_5HZ;
                }
            }
            else
            {
                if (led5State == STATE_LED_FLASH_0_5HZ)
                {
                    LED5 = flashFlag_0_5HZ;
                }
            }
            if (led6State == STATE_LED_FLASH_0_5HZ)
            {
                LED6 = flashFlag_0_5HZ;
            }
            if (led7State == STATE_LED_FLASH_0_5HZ)
            {
                LED7 = flashFlag_0_5HZ;
            }
            if (led8State == STATE_LED_FLASH_0_5HZ)
            {
                LED8 = flashFlag_0_5HZ;
            }
        }
    }
}