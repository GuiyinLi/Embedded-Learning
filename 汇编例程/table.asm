        ORG     0000H
        MOV     A   ,#02H
        MOV     SP  ,#42H
        MOV     41H ,#FFH
        MOV     42H ,#FFH
MAIN:   POP     DPH         ;出栈  DPH=(42H)=FFH SP-1=41H DPH是DPTR的高8位
        POP     DPL         ;出栈  DPL=(41H)=FFH SP-1=40H DPL是DPTR的低8位
        MOV     DPTR,#3000H
        RL      A           ;A<<1 (A)=04H
        MOV     B   ,A      ;(B)=04H
        MOVC    A   ,@A+DPTR;A=(3000H+04H)=(3004H)=50H
        PUSH    Acc         ;入栈 SP+1=41H (41H)=(Acc)=50H 此处Acc不能写为A
        MOV     A   ,B      ;(A)=(B)=04H
        INC     A           ;(A)=04H+1=05H
        MOVC    A   ,@A+DPTR   ;(A)=(3005H)=80H
        PUSH    Acc         ;入栈 SP+1=42H (42H)=(Acc)=80H
        RET                 ;程序返回，将SP堆栈的内容存储到PC中     PC=8050H
        ORG     3000H       ;表的首地址
        DB: 10H,80H,30H,80H,50H,80H
        END

