#include "stdio.h"
#include "s3c2440_soc.h"
int delay(int time)
{
    while(time--);
    return 0;
}
int main()
{
    int key ; //用于读取按键
    int val ; //用于读取寄存器的值
    int key_1=0,key_2=0,key_3=0,key_4=0;
    /* 配置GPB5 6 7 8为输出模式 */
    GPBCON &=~((3<<10) | (3<<12) | (3<<14) | (3<<16)); //先清零
    GPBCON |=((1<<10) | (1<<12) | (1<<14) | (1<<16)); //后置位 01: 输出模式
    GPBDAT |=(15<<5);
    /* 配置四个按键 GPG0 3 5 6为输入引脚 */
    GPGCON =0x00; // 00 输入模式
    /* 循环点亮 二进制累加显示 */
    while(1)
    {
        key = GPGDAT;
        val = GPBDAT; //获取GPBDAT寄存器的值
        /*if(!(key&(1<<0)))  //key_1按下
        {
            GPBDAT &=~(1<<5);  //LED1亮
        }
        else
        {
           GPBDAT |=1<<5;
        }

        if(!(key&(1<<3)))  //key_2按下
        {
            GPBDAT &=~(1<<6);  //LED2亮
        }
        else
        {
           GPBDAT |=1<<6;
        }

        if(!(key&(1<<5)))  //key_4被按下
        {
            GPBDAT &=~(1<<7);  //LED4亮
        }
        else
        {
           GPBDAT |=1<<7;
        }

        if(!(key&(1<<6)))  //key_4按下
        {
            GPBDAT &=~(1<<8);  //LED4亮
        }
        else
        {
           GPBDAT |=1<<8;
        }*/

        if(!(key&(1<<0)))  //key_1按下
        {
            if(!key_1)
            {
                if(val&(1<<5))
                    GPBDAT &=~(1<<5);
                else
                    GPBDAT|=(1<<5);
                key_1=1;
            }
        }
        else
            key_1=0;

        if(!(key&(1<<3)))  //key_2按下
        {
            if(!key_2)
            {
                if(val&(1<<6))
                    GPBDAT &=~(1<<6);
                else
                    GPBDAT|=(1<<6);
                key_2=1;
            }
        }
        else
            key_2=0;

        if(!(key&(1<<5)))  //key_3按下
        {
            if(!key_3)
            {
                if(val&(1<<7))
                    GPBDAT &=~(1<<7);
                else
                    GPBDAT|=(1<<7);
                key_3=1;
            }
        }
        else
            key_3=0;

        if(!(key&(1<<6)))  //key_1按下
        {
            if(!key_4)
            {
                if(val&(1<<8))
                    GPBDAT &=~(1<<8);
                else
                    GPBDAT|=(1<<8);
                key_4=1;
            }
        }
        else
            key_4=0;
    }
    return 1;
}
