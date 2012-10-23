#ifndef _CHIP_COMMON_H_
#define _CHIP_COMMON_H_



#define debug_msg (printf("\n%s,%s[%d]:", __FILE__,__func__ ,__LINE__), printf)

enum INPUT_SIZE_TYPE
{
    TYPE_INPUT_SIZE_702_480 = 0,
    TYPE_INPUT_SIZE_1024_768 = 1,


    TYPE_INPUT_SIZE_DEFAULT = 255,

};



#endif /* USER_H_ */


