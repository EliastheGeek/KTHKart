#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ) 
{
    volatile int returnvalue = PORTD;
    returnvalue = returnvalue >> 8;
    returnvalue &= 0xf;

    return returnvalue;
}

int getbtns(void) 
{
    volatile int returnvalue = PORTD;
    returnvalue = returnvalue >> 5;
    returnvalue &= 0x7;

    return returnvalue;
}
