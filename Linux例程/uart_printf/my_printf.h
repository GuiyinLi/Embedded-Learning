#ifndef _MY_PRINTF_H
#define _MY_PRINTF_H
#include "uart.h"

typedef char * va_list;  //用于定义字符指针 指向format所在地址 然后遍历堆栈
#define _INTSIZEOF(n)    ((sizeof(n) + sizeof(int) -1) &  ~(sizeof(int) - 1))   //指针前进字节的长度(跨过当前变量，移动到下一个变量
#define va_start(ap,v)      ( ap = (va_list)&v + _INTSIZEOF(v))//将ap移动到v所在的位置
#define va_arg(ap,t)        ( *(t *)(ap=ap + _INTSIZEOF(t) , ap - _INTSIZEOF(t)))  //根据参数类型，先将p移动到下一个参数变量，然后获取指针p上次指向的值
#define va_end(ap)      ( ap =(va_list)0) //p=NULL 避免野指针

#define  __out_putchar  send_char
#define MAX_NUMBER_BYTES 64 //打印字符串最大长度
extern int my_printf_test(void);
int printf(const char *fmt, ...);
#endif // _MY_PRINTF_H
