//-----------------
//接收数据----接收数据 与 数据更新 有冲突还需增加控制位

_pin_RECEIVE_C = 1;
if (_pin_RECEIVE_D)
{
    if (b_pin_RECEIVE_D)  // 上次 接收脚的状态
    {                     // 1->1
        r_PIN_RECEIVE_HIGH_TIME++;
        if (r_PIN_RECEIVE_HIGH_TIME > 10)  // 高电平时间太长, 表示传输有误, 初始化BIT计数寄存器
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
    {  // 0->1
        b_pin_RECEIVE_D         = 1;
        r_PIN_RECEIVE_HIGH_TIME = 0;  // 记录高电平寄存器初始化
        if (r_RECEIVE_NUM_COUNT < 64)
        {
            if (r_PIN_RECEIVE_LOW_TIME < C_0_H &&
                r_PIN_RECEIVE_LOW_TIME >= C_0_L)  // 低电平寄存器范围在 250uS-500uS之间, 表示此BIT为 0
            {
                r_receive_buf[0] |= 0x01;
            }
            else
            {
                if (r_PIN_RECEIVE_LOW_TIME > C_1_L &&
                    r_PIN_RECEIVE_LOW_TIME <= C_1_H)  // 低电平寄存器范围在 750uS-1000uS之间, 表示此BIT为 1
                {
                    r_receive_buf[0] |= 0x00;
                }
                else
                {
                    r_RECEIVE_NUM_COUNT = 0;

                    // r_receive_buf[0] = 0;
                    // r_receive_buf[1] = 0;
                    // r_receive_buf[2] = 0;
                    // r_receive_buf[3] = 0;
                    // r_receive_buf[4] = 0;
                    // r_receive_buf[5] = 0;
                    // r_receive_buf[6] = 0;
                    // r_receive_buf[7] = 0;
                }
            }
            if (b_receive_ok == 0)  //  传输结束前 移动BIT位, 保存接收的数据
            {
                _status &= 0xf0;
#asm
                rlc _r_receive_buf[0] rlc _r_receive_buf[1] rlc _r_receive_buf[2] rlc _r_receive_buf[3] rlc
                    _r_receive_buf[4] rlc _r_receive_buf[5] rlc _r_receive_buf[6] rlc _r_receive_buf[7]
#endasm

                    //     _rlc(r_receive_buf[0]);  // 接收数据
                    // _rlc(r_receive_buf[1]);
                    // _rlc(r_receive_buf[2]);
                    // _rlc(r_receive_buf[3]);
                    // _rlc(r_receive_buf[4]);
                    // _rlc(r_receive_buf[5]);
                    // _rlc(r_receive_buf[6]);
                    // _rlc(r_receive_buf[7]);

                    r_RECEIVE_NUM_COUNT++;
            }
            else  //  如果 b_receive_ok 不为 0, 说明上一次数据调整未完成, 不接收新的数据数据
            {
                r_RECEIVE_NUM_COUNT = 0;
            }
        }
        else
        {  // 64BIT 接收完成
            if (r_receive_buf[0] == 0xf0)
            {
                b_receive_ok     = 1;  //  数据接收完成 且正确... 此标志用于对显示缓存的更新
                r_Adjustment_num = 6;
            }
        }
    }
}
else
{
    if (b_pin_RECEIVE_D)  // 上次 接收脚的状态
    {                     // 1->0
        b_pin_RECEIVE_D        = 0;
        r_PIN_RECEIVE_LOW_TIME = 0;
    }
    else
    {  // 0->0
        if (r_PIN_RECEIVE_LOW_TIME < 10)
            r_PIN_RECEIVE_LOW_TIME++;
    }
}

if (b_receive_ok)  // 接收正确后，将接收的数据调整到显示BUF区
{
    if (r_Adjustment_num > 0)
    {
        r_Adjustment_num--;
        if (r_Adjustment_num < 4)  //数据排列---针对数码管
        {
            r_show_buf[r_Adjustment_num] = r_receive_buf[r_Adjustment_num + 1];
        }
        else  //数据排列---针对LED
        {
            r_temp = r_receive_buf[(r_Adjustment_num / 2) + 5];
            if (r_Adjustment_num % 2)
                r_temp = r_temp >> 4;
            r_temp1                          = (r_temp << 1) & 0x10;
            r_temp                           = r_temp & 0x07;
            r_show_led_buf[r_Adjustment_num] = r_temp1 | r_temp;
        }
    }
    else
    {
        b_receive_ok     = 0;
        r_Adjustment_num = 6;
    }
}

if (b_KEY_SEND)  // 开始输出数据
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
                if (r_SEND_KEY_COUNT == 0)  //  传输 KEY 数据,  保留KEY反码
                {
                    r_send_buf1 = ~r_send_buf;  //
                }
                else
                {
                    if (r_SEND_KEY_COUNT == 8)  //  传输KEY反码
                    {
                        r_send_buf = r_send_buf1;  //  KEY值传输完成后, 更新反码到BUF区
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
                r_SEND_BIT_TIME = 7;  // 1: -> LOW 8*250uS
            else
                r_SEND_BIT_TIME = 3;  // 0: -> LOW 4*250uS
        }
        else
        {
            b_PIN_ST = 1;
            if (r_send_buf & 0x80)
                r_SEND_BIT_TIME = 3;  // 1: -> HIGH  4*250uS
            else
                r_SEND_BIT_TIME = 7;       // 0: -> HIGH  8*250uS
            r_send_buf = r_send_buf << 1;  // BUF数据左移一位, 用于下一BIT传输
        }
    }
}