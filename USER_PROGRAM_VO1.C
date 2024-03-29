
#include "..\TKS_GLOBE_VARIES.H"
#include "..\MAIN_PROGRAM_V100\MAIN_PROGRAM_V100.H"

#define _test 1

#define uchar unsigned char
#define uint unsigned int

#define _pin_RECEIVE_D _pa3
#define _pin_RECEIVE_C _pac3
#define _pin_SEND_D _pa7
#define _pin_SEND_C _pac7

#define _pin_SEG_L _pd
#define _pin_SEG_H _pc
#define _pin_COM _pa

//#define		_pin_COM1			_pa1
//#define		_pin_COM2			_pa4
//#define		_pin_COM3			_pa3
//#define		_pin_COM4			_pa7
//#define		_pin_COM1_CT			_pac1
//#define		_pin_COM2_CT			_pac4
//#define		_pin_COM3_CT			_pac3
//#define		_pin_COM4_CT			_pac7

#define _pin_COM3 _pa1
#define _pin_COM4 _pa4
#define _pin_COM2 _pa0
#define _pin_COM1 _pa2
#define _pin_COM3_CT _pac1
#define _pin_COM4_CT _pac4
#define _pin_COM2_CT _pac0
#define _pin_COM1_CT _pac2

#define _pin_SEG1 _pd2
#define _pin_SEG2 _pd3
#define _pin_SEG3 _pc4
#define _pin_SEG4 _pc5
#define _pin_SEG5 _pc6
#define _pin_SEG6 _pc7
#define _pin_SEG7 _pd0
#define _pin_SEG8 _pd1

#define _pin_SEG1_CT _pdc2
#define _pin_SEG2_CT _pdc3
#define _pin_SEG3_CT _pcc4
#define _pin_SEG4_CT _pcc5
#define _pin_SEG5_CT _pcc6
#define _pin_SEG6_CT _pcc7
#define _pin_SEG7_CT _pdc0
#define _pin_SEG8_CT _pdc1

#define _pin_SEG_L_CT _pdc
#define _pin_SEG_H_CT _pcc
#define _pin_COM_CT _pac

#define c_2ms 8 //  8* 250uS
#define C_KEY_DEBOUNCE_TIME 5

#define C_0_L 1 /// 0:   >=C_0_L,   < C_0_H   // 时基 250uS
#define C_0_H 3

#define C_1_L 2 /// 1:   >C_1_L,   <=C_1_H   // 时基 250uS
#define C_1_H 4

//#define		C_pin_COM_OFF					0x8f					//test
#define C_pin_COM_OFF 0x17
#define C_pin_SEG_L_OFF 0x0f
#define C_pin_SEG_H_OFF 0xf0

#pragma rambank0
bit b_2ms, b_receive_ok, b_KEY_ACTION, b_KEY_SEND, b_pin_RECEIVE_D, b_PIN_ST;
uchar r_show_buf[4], r_show_led_buf[6], r_receive_buf[8], r_send_buf, r_send_buf1, r_show_point, r_Adjustment_num;
uchar i, r_SEND_BIT_TIME, r_100ms;
#pragma norambank

uchar r_2ms, r_scan_num, r_temp, r_temp1, r_temp2;
uchar r_PIN_RECEIVE_LOW_TIME, r_PIN_RECEIVE_HIGH_TIME, r_RECEIVE_NUM_COUNT;
uchar r_KEY_STATUS1, r_KEY_STATUS2, r_KEY_BUF[2], r_KEY_DEBOUNCE_TIME, r_SEND_KEY_COUNT;
//uchar			r_show_buf[4],r_show_led_buf[6],r_show_point;

/*
  PD0->C; PD1->B; PD2->E; PD3->D; PC4->G; PC5->DP; PC6->A; PC7->F;
*/
#define SEG_A 0x40
#define SEG_B 0x02
#define SEG_C 0x01
#define SEG_D 0x08
#define SEG_E 0x04
#define SEG_F 0x80
#define SEG_G 0x10
#define SEG_DP 0x20

#define C_SEG_OFF 16

const uchar C_NUM_7SEG[17] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, SEG_B | SEG_C,                                         // 0,1
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G, SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,                         // 2,3
    SEG_G | SEG_B | SEG_C | SEG_F, SEG_A | SEG_G | SEG_C | SEG_D | SEG_F,                                 // 4,5
    SEG_A | SEG_G | SEG_C | SEG_D | SEG_E | SEG_F, SEG_A | SEG_B | SEG_C,                                 // 6,7
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, SEG_A | SEG_B | SEG_C | SEG_D | SEG_G | SEG_F, // 8,9
    SEG_A | SEG_G | SEG_B | SEG_C | SEG_E | SEG_F, SEG_G | SEG_C | SEG_D | SEG_E | SEG_F,                 // A,B
    SEG_D | SEG_E | SEG_G, SEG_G | SEG_B | SEG_C | SEG_D | SEG_E,                                         // C,D
    SEG_G | SEG_C | SEG_D | SEG_E | SEG_F, SEG_A | SEG_G | SEG_E | SEG_F, 0x00                            // E,F,OFF
};

//==============================================
//**********************************************
//==============================================
#pragma vector Interrupt_Extemal @0x04
void Interrupt_Extemal()
{
    _nop();
}

//==============================================
//**********************************************
// CTM0 CCRP INTERRUPT
//==============================================
#pragma vector Interrupt_CTM0_CCRP @0x10
void Interrupt_CTM0_CCRP()
{
    _nop();
}

//==============================================
//**********************************************
// CTM0 CCRA INTERRUPT
// 250uS---定时器
//==============================================
#pragma vector Interrupt_CTM0_CCRA @0x14
void Interrupt_CTM0_CCRA()
{
    _nop();
    // _pin_RECEIVE_C=0;
    // _pin_RECEIVE_D=0;
    r_2ms++;
    if (r_2ms >= c_2ms)
    {
        r_2ms = 0;
        b_2ms = 1;
        r_100ms++;
        if (r_100ms >= 50)
        {
            b_KEY_SEND = 1;
            b_PIN_ST = 1;
            r_SEND_KEY_COUNT = 0;
            r_SEND_BIT_TIME = 0;
            r_100ms = 0;
        }
    }

    // _pin_RECEIVE_D=1;
    // _pin_RECEIVE_D=0;
    // _pin_RECEIVE_D=1;
    // _pin_RECEIVE_D=0;
    // _pin_RECEIVE_D=1;

    r_scan_num++;
    r_temp = 0;
    if (r_scan_num > 13)
        r_scan_num = 0;
    _pin_COM_CT |= C_pin_COM_OFF;
    _pin_SEG_L_CT |= C_pin_SEG_L_OFF;
    _pin_SEG_H_CT |= C_pin_SEG_H_OFF;
    _pin_SEG_L &= ~C_pin_SEG_L_OFF;
    _pin_SEG_H &= ~C_pin_SEG_H_OFF;
    _pin_COM &= ~C_pin_COM_OFF;

    switch (r_scan_num)
    {
    case 0:
        r_temp |= C_NUM_7SEG[r_show_buf[0]];
        _pin_SEG_L |= r_temp;
        _pin_SEG_L_CT &= ~r_temp;
        _pin_COM1 = 0;
        _pin_COM1_CT = 0;
        break;

    case 1:
        r_temp |= C_NUM_7SEG[r_show_buf[0]];
        _pin_SEG_H |= r_temp;
        _pin_SEG_H_CT &= ~r_temp;
        _pin_COM1 = 0;
        _pin_COM1_CT = 0;
        break;

    case 2:
        r_temp |= C_NUM_7SEG[r_show_buf[1]];
        _pin_SEG_H |= r_temp;
        _pin_SEG_H_CT &= ~r_temp;
        _pin_COM2 = 0;
        _pin_COM2_CT = 0;
        break;

    case 3:
        r_temp |= C_NUM_7SEG[r_show_buf[1]];
        _pin_SEG_L |= r_temp;
        _pin_SEG_L_CT &= ~r_temp;
        _pin_COM2 = 0;
        _pin_COM2_CT = 0;
        break;

    case 4:
        r_temp |= C_NUM_7SEG[r_show_buf[2]];
        _pin_SEG_H |= r_temp;
        _pin_SEG_H_CT &= ~r_temp;
        _pin_COM3 = 0;
        _pin_COM3_CT = 0;
        break;

    case 5:
        r_temp |= C_NUM_7SEG[r_show_buf[2]];
        _pin_SEG_L |= r_temp;
        _pin_SEG_L_CT &= ~r_temp;
        _pin_COM3 = 0;
        _pin_COM3_CT = 0;
        break;

    case 6:
        r_temp |= C_NUM_7SEG[r_show_buf[3]];
        _pin_SEG_L |= r_temp;
        _pin_SEG_L_CT &= ~r_temp;
        _pin_COM4 = 0;
        _pin_COM4_CT = 0;
        break;

    case 7:
        r_temp |= C_NUM_7SEG[r_show_buf[3]];
        _pin_SEG_H |= r_temp;
        _pin_SEG_H_CT &= ~r_temp;
        _pin_COM4 = 0;
        _pin_COM4_CT = 0;
        break;

    case 8:
        r_temp |= r_show_led_buf[0];
        _pin_COM |= r_temp;
        _pin_COM_CT &= ~r_temp;
        _pin_SEG1 = 0;
        _pin_SEG1_CT = 0;
        break;

    case 9:

        r_temp |= r_show_led_buf[1];
        _pin_COM |= r_temp;
        _pin_COM_CT &= ~r_temp;

        _pin_SEG2 = 0;
        _pin_SEG2_CT = 0;
        break;

    case 10:
        r_temp |= r_show_led_buf[2];
        _pin_COM |= r_temp;
        _pin_COM_CT &= ~r_temp;
        _pin_SEG3 = 0;
        _pin_SEG3_CT = 0;
        break;

    case 11:
        r_temp |= r_show_led_buf[3];
        _pin_COM |= r_temp;
        _pin_COM_CT &= ~r_temp;
        _pin_SEG4 = 0;
        _pin_SEG4_CT = 0;
        break;

    case 12:
        r_temp |= r_show_led_buf[4];
        _pin_COM |= r_temp;
        _pin_COM_CT &= ~r_temp;
        _pin_SEG5 = 0;
        _pin_SEG5_CT = 0;
        break;

    case 13:
        r_temp |= r_show_led_buf[5];
        _pin_COM |= r_temp;
        _pin_COM_CT &= ~r_temp;
        _pin_SEG6 = 0;
        _pin_SEG6_CT = 0;
        break;

    default:
        r_scan_num = 0;
        break;
    }

    //-----------------
    //接收数据----接收数据 与 数据更新 有冲突还需增加控制位
    _pin_RECEIVE_C = 1;
    if (_pin_RECEIVE_D)
    {
        if (b_pin_RECEIVE_D) // 上次 接收脚的状态
        {                    // 1->1
            r_PIN_RECEIVE_HIGH_TIME++;
            if (r_PIN_RECEIVE_HIGH_TIME > 10) // 高电平时间太长, 表示传输有误, 初始化BIT计数寄存器
            {
                r_RECEIVE_NUM_COUNT = 0;
                /*
//							r_receive_buf[0]=0;
//							r_receive_buf[1]=0;
//							r_receive_buf[2]=0;
//							r_receive_buf[3]=0;
//							r_receive_buf[4]=0;
//							r_receive_buf[5]=0;
//							r_receive_buf[6]=0;
//							r_receive_buf[7]=0;
							*/
            }
        }
        else
        { // 0->1
            b_pin_RECEIVE_D = 1;
            r_PIN_RECEIVE_HIGH_TIME = 0; // 记录高电平寄存器初始化
            if (r_RECEIVE_NUM_COUNT < 64)
            {
                if (r_PIN_RECEIVE_LOW_TIME < C_0_H && r_PIN_RECEIVE_LOW_TIME >= C_0_L) // 低电平寄存器范围在 250uS-500uS之间, 表示此BIT为 0
                {
                    r_receive_buf[0] |= 0x01;
                }
                else
                {
                    if (r_PIN_RECEIVE_LOW_TIME > C_1_L && r_PIN_RECEIVE_LOW_TIME <= C_1_H) // 低电平寄存器范围在 750uS-1000uS之间, 表示此BIT为 1
                    {
                        r_receive_buf[0] |= 0x00;
                    }
                    else
                    {
                        r_RECEIVE_NUM_COUNT = 0;
                        /*
//														r_receive_buf[0]=0;
//														r_receive_buf[1]=0;
//														r_receive_buf[2]=0;
//														r_receive_buf[3]=0;
//														r_receive_buf[4]=0;
//														r_receive_buf[5]=0;
//														r_receive_buf[6]=0;
//														r_receive_buf[7]=0;
														*/
                    }
                }
                if (b_receive_ok == 0) //  传输结束前 移动BIT位, 保存接收的数据
                {
                    _status &= 0xf0;
#asm
                    rlc _r_receive_buf[0] rlc _r_receive_buf[1] rlc _r_receive_buf[2] rlc _r_receive_buf[3] rlc _r_receive_buf[4] rlc _r_receive_buf[5] rlc _r_receive_buf[6] rlc _r_receive_buf[7]
#endasm
                        /*
//									_rlc(r_receive_buf[0]);						// 接收数据
//									_rlc(r_receive_buf[1]);
//									_rlc(r_receive_buf[2]);
//									_rlc(r_receive_buf[3]);
//									_rlc(r_receive_buf[4]);
//									_rlc(r_receive_buf[5]);
//									_rlc(r_receive_buf[6]);
//									_rlc(r_receive_buf[7]);
									*/
                        r_RECEIVE_NUM_COUNT++;
                }
                else //  如果 b_receive_ok 不为 0, 说明上一次数据调整未完成, 不接收新的数据数据
                {
                    r_RECEIVE_NUM_COUNT = 0;
                }
            }
            else
            { // 64BIT 接收完成
                if (r_receive_buf[0] == 0xf0)
                {
                    b_receive_ok = 1; //  数据接收完成 且正确... 此标志用于对显示缓存的更新
                    r_Adjustment_num = 6;
                }
            }
        }
    }
    else
    {
        if (b_pin_RECEIVE_D) // 上次 接收脚的状态
        {                    // 1->0
            b_pin_RECEIVE_D = 0;
            r_PIN_RECEIVE_LOW_TIME = 0;
        }
        else
        { // 0->0
            if (r_PIN_RECEIVE_LOW_TIME < 10)
                r_PIN_RECEIVE_LOW_TIME++;
        }
    }

    if (b_receive_ok) // 接收正确后，将接收的数据调整到显示BUF区
    {
        if (r_Adjustment_num > 0)
        {
            r_Adjustment_num--;
            if (r_Adjustment_num < 4) //数据排列---针对数码管
            {
                r_show_buf[r_Adjustment_num] = r_receive_buf[r_Adjustment_num + 1];
            }
            else //数据排列---针对LED
            {
                r_temp = r_receive_buf[(r_Adjustment_num / 2) + 5];
                if (r_Adjustment_num % 2)
                    r_temp = r_temp >> 4;
                r_temp1 = (r_temp << 1) & 0x10;
                r_temp = r_temp & 0x07;
                r_show_led_buf[r_Adjustment_num] = r_temp1 | r_temp;
            }
        }
        else
        {
            b_receive_ok = 0;
            r_Adjustment_num = 6;
        }
    }

    //-----------------
    //发送数据数据
    //
    if (b_KEY_SEND) // 开始输出数据
    {
        if (r_SEND_BIT_TIME)
        {
            r_SEND_BIT_TIME--;
            _pin_SEND_D = 0;
            if (b_PIN_ST)
                _pin_SEND_C = 1;
            else
                _pin_SEND_C = 0;
        }
        else
        {
            if (b_PIN_ST)
            {
                if (r_SEND_KEY_COUNT < 16)
                {
                    if (r_SEND_KEY_COUNT == 0) //  传输 KEY 数据,  保留KEY反码
                    {
                        r_send_buf1 = ~r_send_buf; //
                    }
                    else
                    {
                        if (r_SEND_KEY_COUNT == 8) //  传输KEY反码
                        {
                            r_send_buf = r_send_buf1; //  KEY值传输完成后, 更新反码到BUF区
                        }
                    }
                    r_SEND_KEY_COUNT++;
                }
                else
                {
                    b_KEY_SEND = 0;
                }

                b_PIN_ST = 0;
                if (r_send_buf & 0x80)
                    r_SEND_BIT_TIME = 7; // 1: -> LOW 8*250uS
                else
                    r_SEND_BIT_TIME = 3; // 0: -> LOW 4*250uS
            }
            else
            {
                b_PIN_ST = 1;
                if (r_send_buf & 0x80)
                    r_SEND_BIT_TIME = 3; // 1: -> HIGH  4*250uS
                else
                    r_SEND_BIT_TIME = 7;      // 0: -> HIGH  8*250uS
                r_send_buf = r_send_buf << 1; // BUF数据左移一位, 用于下一BIT传输
            }
        }
    }
}

//==============================================
//**********************************************
// PTM1 CCRP INTERRUPT
//==============================================
#pragma vector Interrupt_PTM1_CCRP @0x18
void Interrupt_PTM1_CCRP()
{
    _nop();
}

//==============================================
//**********************************************
// PTM1 CCRA INTERRUPT
//==============================================
#pragma vector Interrupt_PTM1_CCRA @0x1C
void Interrupt_PTM1_CCRA()
{
    _nop();
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{
    _papu = 0;
    _pcpu = 0;
    _pdpu = 0;

    _pac = 0xff;
    _pcc = 0xff;
    _pdc = 0xff;
    _pc = 0xff;
    _pd = 0xff;
    _pa = 0xff;

    _lvdc = 0x07;

    _slcdc0 = 0x00;
    _slcdc1 = 0x00;
    _slcdc2 = 0x00;
    _slcdc3 = 0x00;
    _tmpc = 0x00; // PTM 输出功能控制寄存器

    _usr = 0x00;
    _ucr1 = 0x00;
    _ucr2 = 0x00;
    _txr_rxr = 0x00;
    _brg = 0x00;

    _sledc0 = 0xff; // IO驱动电流设定到最大
    _sledc1 = 0xff; // IO驱动电流设定到最大

    _pscr = 0x00; // 时基-时钟源设置寄存器
    //_ctrl=0x10;			// 0x00: 8MHz, 0x10:16MHz , 0x02: 12MHz, 0x11:8MHz

    _iicc0 = 0x00;
    _iicc1 = 0x00;
    _iicd = 0x00;
    _iica = 0x00;

    //;---------定时器TM0配置
    /*--remark:-
	 		//;--------TM0C0 
       _ct0pau=0;								// TM0C0.7---TM0寄存器暂停位; 1: 暂停
       _ct0ck2=1;
       _ct0ck1=1;
       _ct0ck0=1;								// TM0C0[6:4](T0CK[2:0])---TM0 时钟源; 000：Fsys/4; 001:Fsys; 010:Fh/16; 011:Fh/64; 100&101:Ftbc; 110:TCK0上升沿; 111:TCK0下降沿
			 _ct0on=0;									// TM0C0.3---计数器运行控制位
			 
		 //;--------TM0C1  
			 _ct0m1=1;
			 _ct0m0=1;									// TM0C1[7:6](T0M[1:0])---功能选择; 00: 比较匹配输出; 01：捕捉输入模式; 10: PWM模式; 11:定时计数模式
			 _ct0io1=0;
			 _ct0io0=0;								// TM0C1[5:4](T0IO[1:0])---见规格书; 定时模式未使用. PWM模式---10: PWM输出
			 _ct0oc=0;									// TM0C1.3--- 输出脚初始状态; 0: 初始低/低有效； 1: 初始高/高有效
			 _ct0pol=0;								// TM0C1.2--- 输出极性; 0： 同相			 
			 _ct0dpx=0;								// TM0C1.1--- 占空比/频率 比较选择; 0： CCRP周期, CCRA=占空比
			 _ct0cclr=0;								// TM0C1.0--- 计数器周期匹配; 0: CCRP匹配; 1: CCRA匹配
			 
		 //;--------
			 _tm0rp=100;							//  CCRP周期： 256*_tm0rp个TM0时钟周期
			*/
    _ctm0al = 1000 & 0xff; // // 低字节的操作, 仅在其相应的高字节操作执行时发生 //
    _ctm0ah = 1000 / 256;  //  CCRA周期： (256*_tm0ah + _tm0al)个TM0时钟周期

    _ctm0c0 = 0x00;  // CTM0时钟： Fsys/4
    _ctm0c1 = 0x0c1; //   定时计数模式;  CCRA匹配;  定时时间 1000*4/16MHz = 250uS

    _ct0on = 1;

    //;----------INTCG
    _ints1 = 1;
    _ints0 = 1; // _integ[1:0]:INT0触发沿, 11:双边
                //;----------INTC0
    // INTC0[6:4]: 中断请求标志： _int0f, _ocpf, _ovpf
    _inte = 0; //INTC0.1: INT0 中断控制位
    _emi = 1;  //INTC0.0: 总中断
               //;----------MFI1
    //  MFI0[5:4] : 中断请求标志: _t0af (TM0, CCRA), _t0pf (TM0, CCRP)
    //  MFI0[1:0] : 中断控制标志: _ctma0e (TM0, CCRA), _ctmp0e (TM0, CCRP)
    _ctma0e = 1;

    r_receive_buf[0] = 0xf0;
    r_receive_buf[1] = 8;
    r_receive_buf[2] = 8;
    r_receive_buf[3] = 8;
    r_receive_buf[4] = 8;
    r_receive_buf[5] = 8;
    r_receive_buf[6] = 8;
    r_receive_buf[7] = 8;
    b_receive_ok = 1;
    r_Adjustment_num = 6;
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM()
{
    if (b_2ms)
    {
        r_2ms = 0;
        BS82C16A_LIBV413();
    }

    if (SCAN_CYCLEF)
    {
        GET_KEY_BITMAP();

        if (r_KEY_STATUS1 != DATA_BUF[0] || r_KEY_STATUS2 != DATA_BUF[1])
        {
            r_KEY_STATUS1 = DATA_BUF[0];
            r_KEY_STATUS2 = DATA_BUF[1];
            r_KEY_DEBOUNCE_TIME = 0;
        }
        else
        {
            if (r_KEY_DEBOUNCE_TIME < C_KEY_DEBOUNCE_TIME)
            {
                r_KEY_DEBOUNCE_TIME++;
            }
            else
            {
                if (r_KEY_BUF[0] != r_KEY_STATUS1 || r_KEY_BUF[1] != r_KEY_STATUS2)
                {
                    b_KEY_SEND = 0; // 更新按键数据过程中, 不发送
                    r_KEY_BUF[0] = r_KEY_STATUS1;
                    r_KEY_BUF[1] = r_KEY_STATUS2;
                    b_KEY_ACTION = 1;
                    b_KEY_SEND = 1; // 更新按键数据完成后, 发送
                }
            }
        }
    }

    if (r_KEY_BUF[0] == 0x01 && r_KEY_BUF[1] == 0)
    {
        r_temp2 = 0xA1;
        r_show_led_buf[1] = 0x01;
    }
    if (r_KEY_BUF[0] == 0x02 && r_KEY_BUF[1] == 0)
    {
        r_temp2 = 0xA2;
        r_show_led_buf[2] = 0x10;
    }
    if (r_KEY_BUF[0] == 0x04 && r_KEY_BUF[1] == 0)
    {
        r_temp2 = 0xA3;
        r_show_led_buf[3] = 0x10;
    }
    if (r_KEY_BUF[0] == 0x08 && r_KEY_BUF[1] == 0)
        r_temp2 = 0xA4;
    if (r_KEY_BUF[0] == 0x010 && r_KEY_BUF[1] == 0)
        r_temp2 = 0xA5;
    if (r_KEY_BUF[0] == 0x020 && r_KEY_BUF[1] == 0)
        r_temp2 = 0xA6;
    if (r_KEY_BUF[0] == 0x040 && r_KEY_BUF[1] == 0)
        r_temp2 = 0xA7;
    if (r_KEY_BUF[0] == 0x080 && r_KEY_BUF[1] == 0)
        r_temp2 = 0xA8;
    if (r_KEY_BUF[1] == 0x01 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xA9;
    if (r_KEY_BUF[1] == 0x02 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xAA;
    if (r_KEY_BUF[1] == 0x04 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xAB;
    if (r_KEY_BUF[1] == 0x08 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xAC;
    if (r_KEY_BUF[1] == 0x010 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xAD;
    if (r_KEY_BUF[1] == 0x020 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xAE;
    if (r_KEY_BUF[1] == 0x040 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xAF;
    if (r_KEY_BUF[1] == 0x080 && r_KEY_BUF[0] == 0)
        r_temp2 = 0xA0;
    if (r_KEY_BUF[1] == 0 && r_KEY_BUF[0] == 0)
    {
        r_temp2 = 0;
        r_show_led_buf[1] = 0x00;
        r_show_led_buf[2] = 0x00;
        r_show_led_buf[3] = 0x00;
    }

    if (b_KEY_SEND == 0)
        r_send_buf = r_temp2; // 在不传输的时段, 更新按键值

    //  显示测试 按键值
    r_show_buf[1] = r_temp2 & 0x0f;
    r_show_buf[0] = (r_temp2 >> 4) & 0x0f;
    r_show_buf[2] = ~r_show_buf[0];
    r_show_buf[3] = ~r_show_buf[1];
    r_show_led_buf[0] = 0x00; // bit0(PA0): COM2;  bit1(PA1): COM3;  bit2(PA2):COM1;  bit4(PA4):COM4
    //r_show_led_buf[1]=0x01;									// L7: COM2(PA0)  ,SEG2
    //r_show_led_buf[2]=0x10; 								// L14: COM4(PA4) ,SEG3
    //r_show_led_buf[3]=0x10; 								// L10: COM4(PA4) ,SEG4
    r_show_led_buf[4] = 0x00;
    r_show_led_buf[5] = 0x00;
}