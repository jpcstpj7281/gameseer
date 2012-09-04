#include <stdio.h>

extern void I2C_Driver();
void hello_Qbox()
{
    printf("Hello, Qbox!\n");
}

void goodbye_Qbox()
{
    printf("Goodbye, Qbox! \n");
}

void Qbox_driver_init()
{
    hello_Qbox();
    I2C_Driver();
    goodbye_Qbox();
}