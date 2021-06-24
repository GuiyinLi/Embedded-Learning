#include "s3c2440_soc.h"
#include "uart.h"

void uart0_init(int baudrate)
{
    /* 设置引脚用于串口 GPH2->TXD0 GPH3->RXD1 */
    GPHCON &= ~((3<<4)|(3<<6)); //先清零
    GPHCON |= (2<<4)|(2<<6);        //后置位
    GPHUP &=  ~((1<<2)|(1<<3));  //使能内部上拉电阻

    UFCON0=0x00;  //不使用FIFO
    UMCON0=0x00; //不使用流控

    /* 设置数据格式 8n1: 无奇偶校验位 8个数据位 1个停止位*/
    ULCON0 = 0x03;

    /* UBRDIVn = (int)( UART clock / ( buad rate x 16) ) –1
     * UART clock=PCLK (PCLK设置为50MHz)
     * UBRDIVn=(50000000/(115200*16))-1 = 26
     */
    UCON0 = 0x05 ;  //PCLK 中断查询模式 关闭DMA以及一些错误寄存器

    /* 设置波特率为115200 */
    UBRDIV0 =  (PCLK/(baudrate*16))-1;     //26  0x1a
}

//发送一个字节
int send_char(int c)
{
    while( !(UTRSTAT0 & TXD0READY) ); //等待发送缓存器为空
    UTXH0 = c;
}
//接收一个字节
int receive_char(void)
{
    while( !(UTRSTAT0 & RXD0READY) ); //等待接收缓存器收到数据
    return URXH0;
}

int print_string(const char *s)
{
    while(*s)
    {
        send_char(*s++);
    }
    return 0;
}
