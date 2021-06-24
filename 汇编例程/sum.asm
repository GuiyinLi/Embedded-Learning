ADD1:
        MOV     R0  ,#50H   ;n个单字节无符号数的存放首地址
        MOV     R2  ,#n     ;累加项数量n
        MOV     R3  ,#00H   ;存放累加和的高字节
        MOV     R4  ,#00H   ;存放累加器的低字节
LOOP:
        MOV     A   ,R4     ;将上一次的累加记过赋给A A继续累加
        ADD     A   ,@R0    ;依次累加
        MOV     R4  ,A      ;将累加结果的低位赋给R4
        INC     R0          ;指针加1
        CLR     A           ;累加器清零
        ADDC    A   ,R3     ;(A)+(R3)+C->A 相当于A为当前高8位+前k-1次高位累加和
        MOV     R3  ,A      ;将累加结果的高位赋给R3
        DJNZ    R2  ,LOOP   ;判断循环次数是否已到
        END
