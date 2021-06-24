#ifndef _uart_h
#define _uart_h


#define S3C2440_MPLL_200MHZ     ((0x5c<<12)|(0x01<<4)|(0x02))
#define S3C2440_MPLL_400MHZ     ((0x5c<<12)|(0x01<<4)|(0x00))

#define PCLK                         50000000 // 50MHz APB时钟
#define UART_CLK                PCLK//uart工作时钟
#define UART_BAUD_RATE  115200 //波特率
#define UART_BRD                ((UART_CLK/(UART_BAUD_RATE*16))-1)

#define TXD0READY  (1<<2)
#define RXD0READY  (1<<0)
void uart0_init(int baudrate);
int send_char(int c);
int receive_char(void);
int print_string(const char *s);
#endif // _uart_h
