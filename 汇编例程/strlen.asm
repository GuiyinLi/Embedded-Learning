        MOV R0,#2FH ;获取数据首地址
        MOV R2,00H;记录字符串的长度
LOOP:
        INC R0;第一次执行INC后应为第一个字符 考虑到第一个字符为0AH的情况
        INC R2;该类型字符串长度至少为1,所以长度可以先+1
        CJNE @R0,#0AH,LOOP
        END

