//-----------------
//��������----�������� �� ���ݸ��� �г�ͻ�������ӿ���λ

_pin_RECEIVE_C = 1;
if (_pin_RECEIVE_D)
{
    if (b_pin_RECEIVE_D)  // �ϴ� ���սŵ�״̬
    {                     // 1->1
        r_PIN_RECEIVE_HIGH_TIME++;
        if (r_PIN_RECEIVE_HIGH_TIME > 10)  // �ߵ�ƽʱ��̫��, ��ʾ��������, ��ʼ��BIT�����Ĵ���
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
        r_PIN_RECEIVE_HIGH_TIME = 0;  // ��¼�ߵ�ƽ�Ĵ�����ʼ��
        if (r_RECEIVE_NUM_COUNT < 64)
        {
            if (r_PIN_RECEIVE_LOW_TIME < C_0_H &&
                r_PIN_RECEIVE_LOW_TIME >= C_0_L)  // �͵�ƽ�Ĵ�����Χ�� 250uS-500uS֮��, ��ʾ��BITΪ 0
            {
                r_receive_buf[0] |= 0x01;
            }
            else
            {
                if (r_PIN_RECEIVE_LOW_TIME > C_1_L &&
                    r_PIN_RECEIVE_LOW_TIME <= C_1_H)  // �͵�ƽ�Ĵ�����Χ�� 750uS-1000uS֮��, ��ʾ��BITΪ 1
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
            if (b_receive_ok == 0)  //  �������ǰ �ƶ�BITλ, ������յ�����
            {
                _status &= 0xf0;
#asm
                rlc _r_receive_buf[0] rlc _r_receive_buf[1] rlc _r_receive_buf[2] rlc _r_receive_buf[3] rlc
                    _r_receive_buf[4] rlc _r_receive_buf[5] rlc _r_receive_buf[6] rlc _r_receive_buf[7]
#endasm

                    //     _rlc(r_receive_buf[0]);  // ��������
                    // _rlc(r_receive_buf[1]);
                    // _rlc(r_receive_buf[2]);
                    // _rlc(r_receive_buf[3]);
                    // _rlc(r_receive_buf[4]);
                    // _rlc(r_receive_buf[5]);
                    // _rlc(r_receive_buf[6]);
                    // _rlc(r_receive_buf[7]);

                    r_RECEIVE_NUM_COUNT++;
            }
            else  //  ��� b_receive_ok ��Ϊ 0, ˵����һ�����ݵ���δ���, �������µ���������
            {
                r_RECEIVE_NUM_COUNT = 0;
            }
        }
        else
        {  // 64BIT �������
            if (r_receive_buf[0] == 0xf0)
            {
                b_receive_ok     = 1;  //  ���ݽ������ ����ȷ... �˱�־���ڶ���ʾ����ĸ���
                r_Adjustment_num = 6;
            }
        }
    }
}
else
{
    if (b_pin_RECEIVE_D)  // �ϴ� ���սŵ�״̬
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

if (b_receive_ok)  // ������ȷ�󣬽����յ����ݵ�������ʾBUF��
{
    if (r_Adjustment_num > 0)
    {
        r_Adjustment_num--;
        if (r_Adjustment_num < 4)  //��������---��������
        {
            r_show_buf[r_Adjustment_num] = r_receive_buf[r_Adjustment_num + 1];
        }
        else  //��������---���LED
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

if (b_KEY_SEND)  // ��ʼ�������
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
                if (r_SEND_KEY_COUNT == 0)  //  ���� KEY ����,  ����KEY����
                {
                    r_send_buf1 = ~r_send_buf;  //
                }
                else
                {
                    if (r_SEND_KEY_COUNT == 8)  //  ����KEY����
                    {
                        r_send_buf = r_send_buf1;  //  KEYֵ������ɺ�, ���·��뵽BUF��
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
            r_send_buf = r_send_buf << 1;  // BUF��������һλ, ������һBIT����
        }
    }
}