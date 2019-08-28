#define _CCV3_  // ����C�������汾.. --CCG ע��

#include "..\TKS_GLOBE_VARIES.H"
#include "..\MAIN_PROGRAM_V100\MAIN_PROGRAM_V100.H"

#define uchar unsigned char
#define uint unsigned int

volatile _TKS_FLAGA_type bitvar0;

volatile uchar r_temp_bak, r_temp;

#define KEY1 bitvar0.bits.b2
#define KEY2 bitvar0.bits.b3
#define KEY3 bitvar0.bits.b1

#define BEEP _pc0

#define LED1 _pc4
#define LED2 _pc5
#define LED3 _pc6
#define LED4 _pc7
#define LED5 _pb3
#define LED6 _pb4
#define LED7_1 _pb5
#define LED7_2 _pb6

#define KEY4 _pb7

#define IR _pa4

unsigned char rxFlag     = 0;
unsigned char rxBuff[10] = {0};
unsigned char beepFlag   = 0;

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
    LED5 = !LED5;

    rxBuff[9]        = _usr;
    rxBuff[rxFlag++] = _txr_rxr;
}
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{
    // _pac  = 0b11111111;
    // _papu = 0b11111111;
    // _pa   = 0b11111111;

    _pbc  = 0b10000000;
    _pbpu = 0b10000000;
    _pb   = 0b00000000;

    _pcc  = 0b00001110;
    _pcpu = 0b00000000;
    _pc   = 0b00000000;

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

    _usr     = 0x00;
    _ucr1    = 0x80;
    _ucr2    = 0xe4;
    _brg     = 0x67;
    _txr_rxr = 0x00;
    _uarte   = 1;

    _tmpc = 0x00;

    _ctrl = 0x00;

    _tbc |= 0xf0;
    _intc2 |= 0x01;
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM()
{
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
        r_temp       = DATA_BUF[1];
        bitvar0.byte = r_temp;

        if (r_temp != r_temp_bak)
        {
            if (r_temp)
            {
                LED1 = 1;
                LED2 = 1;
                LED3 = 1;
                LED4 = 1;
                // BEEP = 1;
            }
            else
            {
                LED1 = 0;
                LED2 = 0;
                LED3 = 0;
                LED4 = 0;
                //   BEEP = 0;
            }

            if (KEY1)
            {
                beepFlag = 1;
                LED5     = !LED5;
            }
            if (KEY2)
            {
                beepFlag = 1;
                LED6     = !LED6;
            }
            if (KEY3)
            {
                beepFlag = 1;
                LED7_1   = !LED7_1;
                LED7_2   = !LED7_2;
            }
            r_temp_bak = r_temp;

            while (rxFlag)
            {
                while (!_txif)
                    ;
                _txr_rxr = rxBuff[--rxFlag];
                /* code */
            }
        }
    }
}