#define _CCV3_ // 定义C编译器版本.. --CCG 注释

#include "..\TKS_GLOBE_VARIES.H"
#include "..\MAIN_PROGRAM_V100\MAIN_PROGRAM_V100.H"

#define uchar unsigned char
#define uint unsigned int

volatile _TKS_FLAGA_type bitvar0;

volatile uchar r_temp_bak, r_temp;

#define f_KeyDown bitvar0.bits.b0

#define MOTO1 _pb4
#define MOTO2 _pb5
#define MOTO3 _pb6
#define BL1 _pb7
#define BUZ1 _pc0
#define LED1 _pc1
#define LED2 _pc2
#define LED3 _pc3
#define LED4 _pc4
#define LED5 _pc5
#define DIN _pc6
#define SCLK _pc7
#define IR _pa4

//==============================================
//**********************************************
//==============================================
//#pragma vector  Interrupt_Extemal        @ 0x04
//void Interrupt_Extemal()

void __attribute((interrupt(0x04))) Interrupt_Extemal(void)
{
    GCC_NOP();
}

//==============================================
//**********************************************
// CTM0 CCRP INTERRUPT
//==============================================
//#pragma vector  Interrupt_CTM0_CCRP        @ 0x10
//void Interrupt_CTM0_CCRP()

void __attribute((interrupt(0x10))) Interrupt_CTM0_CCRP(void)
{
    GCC_NOP();
}

//==============================================
//**********************************************
// CTM0 CCRA INTERRUPT
// 250uS---定时器
//==============================================
//#pragma vector  Interrupt_CTM0_CCRA       @ 0x14
//void Interrupt_CTM0_CCRA()
void __attribute((interrupt(0x14))) Interrupt_CTM0_CCRA(void)
{

    GCC_CLRWDT(); //_clrwdt();
}

//==============================================
//**********************************************
// PTM1 CCRP INTERRUPT
//==============================================
//#pragma vector  Interrupt_PTM1_CCRP       @ 0x18
//void Interrupt_PTM1_CCRP()

void __attribute((interrupt(0x18))) Interrupt_PTM1_CCRP(void)
{
    GCC_NOP(); //_nop();
}

//==============================================
//**********************************************
// PTM1 CCRA INTERRUPT
//==============================================
//#pragma vector  Interrupt_PTM1_CCRA        @ 0x1C
//void Interrupt_PTM1_CCRA()

void __attribute((interrupt(0x1c))) Interrupt_PTM1_CCRA(void)
{
}
//==============================================
//**********************************************
// TB1 INTERRUPT
//==============================================
//#pragma vector  Interrupt_TB1      @ 0x20
//void Interrupt_TB1()

void __attribute((interrupt(0x20))) Interrupt_TB1(void)
{
    LED5 = !LED5;
}
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{

    _pac = 0b11111111;
    _papu = 0b11111111;
    _pa = 0b11111111;

    _pbc = 0b00001111;
    _pbpu = 0b00000000;
    _pb = 0b00000000;

    _pcc = 0b00000000;
    _pcpu = 0b00000000;
    _pc = 0b00000000;

    _lvdc = 0x00;

    _sledc0 = 0xff;
    _sledc1 = 0xff;

    _eea = 0x00;
    _eed = 0x00;

    _i2ctoc = 0x00;
    _iicc0 = 0x00;
    _iicc1 = 0x00;
    _iicd = 0x00;
    _iica = 0x00;
    _usr = 0x00;
    _ucr1 = 0x00;
    _ucr2 = 0x00;
    _brg = 0x00;
    _txr_rxr = 0x00;

    _tmpc = 0x00;

    _slcdc0 = 0x00;
    _slcdc1 = 0x00;
    _slcdc2 = 0x00;
    _slcdc3 = 0x00;

    _ctrl = 0x00;

    _tbc |= 0xf0;
    _intc2 |= 0x01;
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM()
{

    if (SCAN_CYCLEF)
    {
        GET_KEY_BITMAP();
        r_temp = DATA_BUF[0];
        /*	 	    if(r_temp==r_temp_bak) 
			{   
			  	if(f_KeyDown==1)
			  	{
			  	  f_KeyDown = 0;
				  if(r_temp_bak&0x01)
				  LED1 =! LED1;
				  if(r_temp_bak&0x02)
				  LED2 =! LED2 ;			  
				  if(r_temp_bak&0x04)
				  LED3 =! LED3 ;			  
				  if(r_temp_bak&0x08)
				  LED4 =! LED4;
				 
			  	}		  	 
			}
			else
			{
			  	r_temp_bak = r_temp;
			  	f_KeyDown=1;
			}*/
        if (r_temp != r_temp_bak)
        {
            if (r_temp & 0x01)
                LED1 = !LED1;
            if (r_temp & 0x02)
                LED2 = !LED2;
            if (r_temp & 0x04)
                LED3 = !LED3;
            if (r_temp & 0x08)
                LED4 = !LED4;
            r_temp_bak = r_temp;
        }
    }
}