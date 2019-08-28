#ifndef _BS82C16A_3_H_
#define _BS82C16A_3_H_

unsigned char _iar0	@0x00;
unsigned char _mp0	@0x01;
unsigned char _iar1	@0x02;
unsigned char _mp1	@0x03;
unsigned char _bp	@0x04;
unsigned char _acc	@0x05;
unsigned char _pcl	@0x06;
unsigned char _tblp	@0x07;
unsigned char _tblh	@0x08;
unsigned char _tbhp	@0x09;
unsigned char _status	@0x0A;
unsigned char _smod	@0x0B;
unsigned char _integ	@0x0D;
unsigned char _intc0	@0x0E;
unsigned char _intc1	@0x0F;
unsigned char _intc2	@0x10;
unsigned char _intc3	@0x11;
unsigned char _lvdc	@0x12;
unsigned char _lvrc	@0x13;
unsigned char _pa	@0x14;
unsigned char _pac	@0x15;
unsigned char _papu	@0x16;
unsigned char _pawu	@0x17;
unsigned char _sledc0	@0x18;
unsigned char _sledc1	@0x19;
unsigned char _wdtc	@0x1A;
unsigned char _tbc	@0x1B;
unsigned char _pscr	@0x1C;
unsigned char _eea	@0x1E;
unsigned char _eed	@0x1F;
unsigned char _pb	@0x20;
unsigned char _pbc	@0x21;
unsigned char _pbpu	@0x22;
unsigned char _i2ctoc	@0x23;
unsigned char _iicc0	@0x24;
unsigned char _iicc1	@0x25;
unsigned char _iicd	@0x26;
unsigned char _iica	@0x27;
unsigned char _usr	@0x28;
unsigned char _ucr1	@0x29;
unsigned char _ucr2	@0x2A;
unsigned char _brg	@0x2B;
unsigned char _txr_rxr	@0x2C;
unsigned char _tmpc	@0x30;
unsigned char _slcdc0	@0x33;
unsigned char _slcdc1	@0x34;
unsigned char _slcdc2	@0x35;
unsigned char _slcdc3	@0x36;
unsigned char _pc	@0x39;
unsigned char _pcc	@0x3A;
unsigned char _pcpu	@0x3B;
unsigned char _ctrl	@0x3D;
unsigned char _pd	@0x41;
unsigned char _pdc	@0x42;
unsigned char _pdpu	@0x43;
unsigned char _tktmr	@0x44;
unsigned char _tkc0	@0x45;
unsigned char _tk16dl	@0x46;
unsigned char _tk16dh	@0x47;
unsigned char _tkc1	@0x48;
unsigned char _tkm016dl	@0x49;
unsigned char _tkm016dh	@0x4A;
unsigned char _tkm0rol	@0x4B;
unsigned char _tkm0roh	@0x4C;
unsigned char _tkm0c0	@0x4D;
unsigned char _tkm0c1	@0x4E;
unsigned char _tkm116dl	@0x4F;
unsigned char _tkm116dh	@0x50;
unsigned char _tkm1rol	@0x51;
unsigned char _tkm1roh	@0x52;
unsigned char _tkm1c0	@0x53;
unsigned char _tkm1c1	@0x54;
unsigned char _tkm216dl	@0x55;
unsigned char _tkm216dh	@0x56;
unsigned char _tkm2rol	@0x57;
unsigned char _tkm2roh	@0x58;
unsigned char _tkm2c0	@0x59;
unsigned char _tkm2c1	@0x5A;
unsigned char _tkm316dl	@0x5B;
unsigned char _tkm316dh	@0x5C;
unsigned char _tkm3rol	@0x5D;
unsigned char _tkm3roh	@0x5E;
unsigned char _tkm3c0	@0x5F;
unsigned char _tkm3c1	@0x60;
unsigned char _ctm0c0	@0x61;
unsigned char _ctm0c1	@0x62;
unsigned char _ctm0dl	@0x63;
unsigned char _ctm0dh	@0x64;
unsigned char _ctm0al	@0x65;
unsigned char _ctm0ah	@0x66;
unsigned char _ptm0c0	@0x67;
unsigned char _ptm0c1	@0x68;
unsigned char _ptm0dl	@0x69;
unsigned char _ptm0dh	@0x6A;
unsigned char _ptm0al	@0x6B;
unsigned char _ptm0ah	@0x6C;
unsigned char _ptm0rpl	@0x6D;
unsigned char _ptm0rph	@0x6E;
#define _eec	_0140

#define _dmbp0	_04_0
#define _dmbp1	_04_1
#define _c	_0a_0
#define _ac	_0a_1
#define _z	_0a_2
#define _ov	_0a_3
#define _pdf	_0a_4
#define _to	_0a_5
#define _hlclk	_0b_0
#define _idlen	_0b_1
#define _hto	_0b_2
#define _lto	_0b_3
#define _cks0	_0b_5
#define _cks1	_0b_6
#define _cks2	_0b_7
#define _ints0	_0d_0
#define _ints1	_0d_1
#define _emi	_0e_0
#define _inte	_0e_1
#define _tkme	_0e_2
#define _tb0e	_0e_3
#define _intf	_0e_4
#define _tkmf	_0e_5
#define _tb0f	_0e_6
#define _ctmp0e	_0f_0
#define _ctma0e	_0f_1
#define _ptmp1e	_0f_2
#define _ptma1e	_0f_3
#define _ctmp0f	_0f_4
#define _ctma0f	_0f_5
#define _ptmp1f	_0f_6
#define _ptma1f	_0f_7
#define _tb1e	_10_0
#define _iice	_10_1
#define _dee	_10_2
#define _uarte	_10_3
#define _tb1f	_10_4
#define _iicf	_10_5
#define _def	_10_6
#define _uartf	_10_7
#define _lvde	_11_0
#define _lvdf	_11_4
#define _vlvd0	_12_0
#define _vlvd1	_12_1
#define _vlvd2	_12_2
#define _lvden	_12_4
#define _lvdo	_12_5
#define _lvs0	_13_0
#define _lvs1	_13_1
#define _lvs2	_13_2
#define _lvs3	_13_3
#define _lvs4	_13_4
#define _lvs5	_13_5
#define _lvs6	_13_6
#define _lvs7	_13_7
#define _pa0	_14_0
#define _pa1	_14_1
#define _pa2	_14_2
#define _pa3	_14_3
#define _pa4	_14_4
#define _pa7	_14_7
#define _pac0	_15_0
#define _pac1	_15_1
#define _pac2	_15_2
#define _pac3	_15_3
#define _pac4	_15_4
#define _pac7	_15_7
#define _papu0	_16_0
#define _papu1	_16_1
#define _papu2	_16_2
#define _papu3	_16_3
#define _papu4	_16_4
#define _papu7	_16_7
#define _pawu0	_17_0
#define _pawu1	_17_1
#define _pawu2	_17_2
#define _pawu3	_17_3
#define _pawu4	_17_4
#define _pawu7	_17_7
#define _paps0	_18_0
#define _paps1	_18_1
#define _paps2	_18_2
#define _paps3	_18_3
#define _pbps0	_18_4
#define _pbps1	_18_5
#define _pbps2	_18_6
#define _pbps3	_18_7
#define _pcps0	_19_0
#define _pcps1	_19_1
#define _pcps2	_19_2
#define _pcps3	_19_3
#define _pdps0	_19_4
#define _pdps1	_19_5
#define _ws0	_1a_0
#define _ws1	_1a_1
#define _ws2	_1a_2
#define _we0	_1a_3
#define _we1	_1a_4
#define _we2	_1a_5
#define _we3	_1a_6
#define _we4	_1a_7
#define _tb00	_1b_0
#define _tb01	_1b_1
#define _tb02	_1b_2
#define _tb0on	_1b_3
#define _tb10	_1b_4
#define _tb11	_1b_5
#define _tb12	_1b_6
#define _tb1on	_1b_7
#define _clksel00	_1c_0
#define _clksel01	_1c_1
#define _clksel10	_1c_4
#define _clksel11	_1c_5
#define _pb0	_20_0
#define _pb1	_20_1
#define _pb2	_20_2
#define _pb3	_20_3
#define _pb4	_20_4
#define _pb5	_20_5
#define _pb6	_20_6
#define _pb7	_20_7
#define _pbc0	_21_0
#define _pbc1	_21_1
#define _pbc2	_21_2
#define _pbc3	_21_3
#define _pbc4	_21_4
#define _pbc5	_21_5
#define _pbc6	_21_6
#define _pbc7	_21_7
#define _pbpu0	_22_0
#define _pbpu1	_22_1
#define _pbpu2	_22_2
#define _pbpu3	_22_3
#define _pbpu4	_22_4
#define _pbpu5	_22_5
#define _pbpu6	_22_6
#define _pbpu7	_22_7
#define _i2ctos0	_23_0
#define _i2ctos1	_23_1
#define _i2ctos2	_23_2
#define _i2ctos3	_23_3
#define _i2ctos4	_23_4
#define _i2ctos5	_23_5
#define _i2ctof	_23_6
#define _i2ctoen	_23_7
#define _iicen	_24_1
#define _i2cdbnc0	_24_2
#define _i2cdbnc1	_24_3
#define _iicrxak	_25_0
#define _iicamwu	_25_1
#define _iicsrw	_25_2
#define _iictxak	_25_3
#define _iichtx	_25_4
#define _iichbb	_25_5
#define _iichaas	_25_6
#define _iichcf	_25_7
#define _iicd0	_26_0
#define _iicd1	_26_1
#define _iicd2	_26_2
#define _iicd3	_26_3
#define _iicd4	_26_4
#define _iicd5	_26_5
#define _iicd6	_26_6
#define _iicd7	_26_7
#define _iica0	_27_1
#define _iica1	_27_2
#define _iica2	_27_3
#define _iica3	_27_4
#define _iica4	_27_5
#define _iica5	_27_6
#define _iica6	_27_7
#define _txif	_28_0
#define _tidle	_28_1
#define _rxif	_28_2
#define _ridle	_28_3
#define _oerr	_28_4
#define _ferr	_28_5
#define _nf	_28_6
#define _perr	_28_7
#define _tx8	_29_0
#define _rx8	_29_1
#define _txbrk	_29_2
#define _stops	_29_3
#define _prt	_29_4
#define _pren	_29_5
#define _bno	_29_6
#define _uarten	_29_7
#define _teie	_2a_0
#define _tiie	_2a_1
#define _rie	_2a_2
#define _wake	_2a_3
#define _adden	_2a_4
#define _brgh	_2a_5
#define _rxen	_2a_6
#define _txen	_2a_7
#define _brg0	_2b_0
#define _brg1	_2b_1
#define _brg2	_2b_2
#define _brg3	_2b_3
#define _brg4	_2b_4
#define _brg5	_2b_5
#define _brg6	_2b_6
#define _brg7	_2b_7
#define _txrx0	_2c_0
#define _txrx1	_2c_1
#define _txrx2	_2c_2
#define _txrx3	_2c_3
#define _txrx4	_2c_4
#define _txrx5	_2c_5
#define _txrx6	_2c_6
#define _txrx7	_2c_7
#define _tm0pc0	_30_0
#define _tm0pc1	_30_1
#define _tm1pc0	_30_2
#define _tm1pc1	_30_3
#define _com0en	_33_0
#define _com1en	_33_1
#define _com2en	_33_2
#define _com3en	_33_3
#define _lcden	_33_4
#define _isel0	_33_5
#define _isel1	_33_6
#define _frame	_33_7
#define _seg0en	_34_0
#define _seg1en	_34_1
#define _seg2en	_34_2
#define _seg3en	_34_3
#define _seg4en	_34_4
#define _seg5en	_34_5
#define _seg6en	_34_6
#define _seg7en	_34_7
#define _seg8en	_35_0
#define _seg9en	_35_1
#define _seg10en	_35_2
#define _seg11en	_35_3
#define _seg12en	_35_4
#define _seg13en	_35_5
#define _seg14en	_35_6
#define _seg15en	_35_7
#define _seg16en	_36_0
#define _seg17en	_36_1
#define _seg18en	_36_2
#define _seg19en	_36_3
#define _pc0	_39_0
#define _pc1	_39_1
#define _pc2	_39_2
#define _pc3	_39_3
#define _pc4	_39_4
#define _pc5	_39_5
#define _pc6	_39_6
#define _pc7	_39_7
#define _pcc0	_3a_0
#define _pcc1	_3a_1
#define _pcc2	_3a_2
#define _pcc3	_3a_3
#define _pcc4	_3a_4
#define _pcc5	_3a_5
#define _pcc6	_3a_6
#define _pcc7	_3a_7
#define _pcpu0	_3b_0
#define _pcpu1	_3b_1
#define _pcpu2	_3b_2
#define _pcpu3	_3b_3
#define _pcpu4	_3b_4
#define _pcpu5	_3b_5
#define _pcpu6	_3b_6
#define _pcpu7	_3b_7
#define _wrf	_3d_0
#define _lvrf	_3d_2
#define _lxtlp	_3d_3
#define _hircs0	_3d_4
#define _hircs1	_3d_5
#define _fsyson	_3d_7
#define _pd0	_41_0
#define _pd1	_41_1
#define _pd2	_41_2
#define _pd3	_41_3
#define _pdc0	_42_0
#define _pdc1	_42_1
#define _pdc2	_42_2
#define _pdc3	_42_3
#define _pdpu0	_43_0
#define _pdpu1	_43_1
#define _pdpu2	_43_2
#define _pdpu3	_43_3
#define _tk16s0	_45_0
#define _tk16s1	_45_1
#define _tscs	_45_2
#define _tk16ov	_45_3
#define _tkcfov	_45_4
#define _tkst	_45_5
#define _tkrcov	_45_6
#define _tkfs0	_48_0
#define _tkfs1	_48_1
#define _m0sof0	_4d_0
#define _m0sof1	_4d_1
#define _m0sof2	_4d_2
#define _m0sofc	_4d_3
#define _m0filen	_4d_4
#define _m0dfen	_4d_5
#define _m0mxs0	_4d_6
#define _m0mxs1	_4d_7
#define _m0k1io	_4e_0
#define _m0k2io	_4e_1
#define _m0k3io	_4e_2
#define _m0k4io	_4e_3
#define _m0koen	_4e_4
#define _m0roen	_4e_5
#define _m0tss	_4e_7
#define _m1sof0	_53_0
#define _m1sof1	_53_1
#define _m1sof2	_53_2
#define _m1sofc	_53_3
#define _m1filen	_53_4
#define _m1dfen	_53_5
#define _m1mxs0	_53_6
#define _m1mxs1	_53_7
#define _m1k1io	_54_0
#define _m1k2io	_54_1
#define _m1k3io	_54_2
#define _m1k4io	_54_3
#define _m1koen	_54_4
#define _m1roen	_54_5
#define _m1tss	_54_7
#define _m2sof0	_59_0
#define _m2sof1	_59_1
#define _m2sof2	_59_2
#define _m2sofc	_59_3
#define _m2filen	_59_4
#define _m2dfen	_59_5
#define _m2mxs0	_59_6
#define _m2mxs1	_59_7
#define _m2k1io	_5a_0
#define _m2k2io	_5a_1
#define _m2k3io	_5a_2
#define _m2k4io	_5a_3
#define _m2koen	_5a_4
#define _m2roen	_5a_5
#define _m2tss	_5a_7
#define _m3sof0	_5f_0
#define _m3sof1	_5f_1
#define _m3sof2	_5f_2
#define _m3sofc	_5f_3
#define _m3filen	_5f_4
#define _m3dfen	_5f_5
#define _m3mxs0	_5f_6
#define _m3mxs1	_5f_7
#define _m3k1io	_60_0
#define _m3k2io	_60_1
#define _m3k3io	_60_2
#define _m3k4io	_60_3
#define _m3koen	_60_4
#define _m3roen	_60_5
#define _m3tss	_60_7
#define _ct0rp0	_61_0
#define _ct0rp1	_61_1
#define _ct0rp2	_61_2
#define _ct0on	_61_3
#define _ct0ck0	_61_4
#define _ct0ck1	_61_5
#define _ct0ck2	_61_6
#define _ct0pau	_61_7
#define _ct0cclr	_62_0
#define _ct0dpx	_62_1
#define _ct0pol	_62_2
#define _ct0oc	_62_3
#define _ct0io0	_62_4
#define _ct0io1	_62_5
#define _ct0m0	_62_6
#define _ct0m1	_62_7
#define _pt0on	_67_3
#define _pt0ck0	_67_4
#define _pt0ck1	_67_5
#define _pt0ck2	_67_6
#define _pt0pau	_67_7
#define _pt0cclr	_68_0
#define _pt0dpx	_68_1
#define _pt0pol	_68_2
#define _pt0oc	_68_3
#define _pt0io0	_68_4
#define _pt0io1	_68_5
#define _pt0m0	_68_6
#define _pt0m1	_68_7


#endif // _BS82C16A_3_H_
