        ORG 0000H   ;保证目标程序在0000H处执行
MIAN:   MOV SP ,#60H
        MOV B , #01H  ;赋初值
MLP:    MOV A,B
        MOV P1,A
        RL  A       ;累加器循环左移
        MOV B,A
        LCALL   DELAY
DELAY:  MOV R5,#200
DLP：   DJNZ R5,DLP   ;寄存器减一 不为零则转移
        RET  ;字程序返回 返回跳转处->MLP

        END ;程序结束

