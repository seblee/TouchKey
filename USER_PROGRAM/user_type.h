#ifndef _USER_TYPE_H_
#define _USER_TYPE_H_

typedef struct
{
    unsigned char s0 : 2;
    unsigned char s1 : 2;
    unsigned char s2 : 2;
    unsigned char s3 : 2;
} _STATE_bits;

typedef union
{
    _STATE_bits sbits;
    unsigned char byte;
} _USR_FLAGA_type;

#endif