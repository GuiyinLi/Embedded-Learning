        ORG     2000H
MAX     EQU     50H         ;定义最大值存储单元
        MOV     R0  ,#21H   ;将存储数据首地址放在R0中
        MOV     MAX ,#00H   ;将最大值存储单元中的内容清零
        MOV     R1  ,#20H   ;计数变量存入R1中 数据一共20H个，首地址在21H
LOOP:
        MOV     A   ,@R0    ;获取当前地址中的无符号数
        CLR     C           ;在进行运算之前，将进位标志位清零
        SUBB    A   ,MAX    ;带借位的减法 A=A-MAX                                JC:进位标志位为1则转移
        JNC     BIG_PRG     ;如果没有借位 则跳转到BIG_PRG中,即若@R0>MAX,则令MAX=R0,JNC:进位标志位为0则转移
M_PRT:
        INC     R0          ;否则不进行交换 继续遍历下一个无符号数
        DJNZ    R1  ,LOOP   ;R1-- R1!=0则继续遍历循环
        SJMP    M_END       ;否则程序结束
BIG_PRG:
        MOV MAX ,@R0        ;存储当前最大值
        SJMP    M_PRT       ;跳转到M_PRT
M_END:
        END                 ;程序结束
