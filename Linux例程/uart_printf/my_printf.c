#include "my_printf.h"

unsigned char hex_tab[] = {'0','1','2','3','4','5','6','7',\
                           '8','9','a','b','c','d','e','f'
                          };
//引用uart.c中的字符打印函数
static int outc(int c)
{
    __out_putchar(c);
    return 0;
}

static int outs(const char *s)
{
    while(*s)
        __out_putchar(*s++);
    return 0;
}

/*
 * n :  数字内容
 * base : 进制 10 8 16
 * lead : 前导字符串 通常为字节对齐的空格
 * maxwidth : 字节对齐数  %100d  左移100个空格对齐
 */
static int out_num(long n, int base, char lead, int maxwidth)
{
    unsigned long m = 0; //用于缓存n
    char buf[MAX_NUMBER_BYTES] ;
    char *s = buf + sizeof(buf);  //开辟字符串空间
    int count = 0,i = 0;
    *--s = '\0'; //加结束符

    if(n<0)
        m=-n;    //先把负数变成正数 最后再加负号
    else
        m=n;
    do
    {
        *--s = hex_tab[m%base];
        count++;
    }
    while((m/=base)!=0);  //通过查表法将十进制数转换成目标进制数
    if( maxwidth&&count<maxwidth) //添加前导字符串
    {
        for(i = maxwidth - count ; i ; i--)
            *--s = lead;
    }
    return outs(s); //打印并返回
}
/*reference :   int vprintf(const char *format, va_list ap); */
static int my_vprintf(const char *fmt, va_list ap)
{
    char lead = ' ';
    int maxwidth  = 0;

    for(; *fmt!='\0'; fmt++)
    {
        if(*fmt!='%')
        {
            outc(*fmt);    //遇到普通字符串则打印
            continue;
        }
        //format : %08d, %8d,%d,%u,%x,%f,%c,%s 遇到格式字符则进行解析
        fmt++;  //略过%，该符号只是格式字符的标志
        if(*fmt == '0') //靠左对齐
        {
            lead = '0';
            fmt++;
        }
        lead = ' ';
        maxwidth = 0;
        while(*fmt>'0' && *fmt<='9')//左/右对齐字节数
        {
            maxwidth *= 10; //eg: 102 计算百位1 十位0 个位2 然后相加 从而计算出对齐字节数
            maxwidth += (*fmt- '0'); //将字符串转换成数字
            fmt++;
        }
        switch(*fmt)
        {
        case 'd' :
            out_num(va_arg(ap,int),10,lead,maxwidth);
            break;
        case 'o' :
            out_num(va_arg(ap,unsigned int),8,lead,maxwidth);
            break;
        case 'u' :
            out_num(va_arg(ap,unsigned int),10,lead,maxwidth);
            break;
        case 'x' :
            out_num(va_arg(ap,unsigned int),16,lead,maxwidth);
            break;
        case 'c' :
            outc(va_arg(ap,char));
            break;
        case 's' :
            outs(va_arg(ap,char *));
            break;
        default :
            outc(*fmt);  //其余均为普通字符串
            break;
        }
    }
    return 0;
}
//reference :  int printf(const char *format, ...);
int printf(const char *fmt, ...)
{
    va_list ap;             //先创建一个指向堆栈的指针
    va_start(ap,fmt);        //移动到第一个固定参数变量所在位置
    my_vprintf(fmt,ap);     //遍历堆栈变量 并且打印出来
    va_end(ap);            //清空指针ap 避免野指针
    return 0;             //打印结束 返回0
}

int my_printf_test(void)
{
    printf("This is www.100ask.org   my_printf test\n\r") ;
    printf("test char           =%c,%c\n\r", 'A','a') ;
    printf("test decimal number =%d\n\r",    123456) ;
    printf("test decimal number =%d\n\r",    -123456) ;
    printf("test hex     number =0x%x\n\r",  0x55aa55aa) ;
    printf("test string         =%s\n\r",    "www.100ask.org") ;
    printf("num=%08d\n\r",   12345);
    printf("num=%8d\n\r",    12345);
    printf("num=0x%08x\n\r", 0x12345);
    printf("num=0x%8x\n\r",  0x12345);
    printf("num=0x%02x\n\r", 0x1);
    printf("num=0x%2x\n\r",  0x1);

    printf("num=%05d\n\r", 0x1);
    printf("num=%5d\n\r",  0x1);

    return 0;
}
