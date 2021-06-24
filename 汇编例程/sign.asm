;X存放在40H Y存放在41H 计算符号函数
SIGNFUC:
            MOV     A       ,40H        ;读取X的值 存入累加器A中
            CJNE    A       ,#00H,NZEAR ;不等于零则区分正负
            AJMP    NEGT                ;等于零则直接赋值  x=0 y=0
NZEAR:                                  ;JB:直接寻址位为1则转移
            JB      Acc.7   ,POSI       ;根据符号位判断正负 <0则跳转到POSI
            MOV     A,      #01H        ;x>0 y=1
            AJMP    NEGT
POSI:
            MOV     A       ,#81H       ;x<0 y=-1
            AJMP    NEGT
NEGT:
            MOV     41H     ,A
            END
