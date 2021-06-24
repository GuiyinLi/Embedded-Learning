#include "stdio.h"

int delay(int time)
{
    while(time--);
    return 0;
}
int main()
{
    unsigned int *pGPBCON=(unsigned int *)0x56000010;
    unsigned int *pGPBDATA=(unsigned int *)0x56000014;
    /* 配置GPB5 6 7 8为输出模式 */
    *pGPBCON &=~((3<<10) | (3<<12) | (3<<14) | (3<<16)); //将对应位清零
    *pGPBCON |=((1<<10) | (1<<12) | (1<<14) | (1<<16)); //将对应为置1
    *pGPBDATA |=(15<<5);

         *pGPBDATA &=~(1<<5);
         delay(5000000);
          *pGPBDATA |=(1<<5);
          delay(5000000);



    return 1;
}
