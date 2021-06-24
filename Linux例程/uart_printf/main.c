#include "s3c2440_soc.h"
#include "uart.h"
#include "my_printf.h"
#include <stdio.h>
int  main()
{
    unsigned char ch;
    uart0_init(115200);
    my_printf_test();
    while(1)
    {
        ch=receive_char();
        if(ch == '\r')
        {
            send_char('\n');
        }
        else if(ch == '\n')
        {
            send_char('\r');
        }
        send_char(ch);
    }
    return 0;
}
