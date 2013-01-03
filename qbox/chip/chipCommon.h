#ifndef _CHIP_COMMON_H_
#define _CHIP_COMMON_H_



#define debug_msg (printf("\n%s,%s[%d]:", __FILE__,__func__ ,__LINE__), printf)

enum INPUT_SIZE_TYPE
{
    TYPE_INPUT_SIZE_702_480 = 0,
    TYPE_INPUT_SIZE_800_600 = 2,
    TYPE_INPUT_SIZE_1024_768_60 = 3,
    TYPE_INPUT_SIZE_1280_1024_60 = 4,
    TYPE_INPUT_SIZE_1600_1200_60 = 5,

    TYPE_INPUT_SIZE_DEFAULT = 255,

};



#endif /* USER_H_ */


