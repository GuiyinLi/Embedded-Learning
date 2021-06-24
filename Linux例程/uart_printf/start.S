@ 以下为时钟相关寄存器地址

.equ    LOCKTIME   ,  0x4c000000        
.equ    MPLLCON    ,  0x4c000004       
.equ    CLKDIVN    ,  0x4c000014       
.equ    CAMDIVN    ,  0x4c000018       
.text
.global _start

_start:

	/* 初始化堆栈指针 */
	mov r1 , #0
	ldr r0 , [r1] //读取0地址的值进行备份
	str r1 , [r1] //0->[0] 将0写入0地址
	ldr r2 , [r1] //r2=[0]将0地址的数据读取出来，存放到r2中
	cmp r1 ,r2 //比较r1 r2 比较写入值和读取值是否相同
	ldr sp, =0x40000000+4096
	moveq sp , #4096 //如果r1 r2相同 则sp=4096
	streq r0 , [r1] //恢复原来的值
	
	/* 关闭看门狗 */
	ldr r0 , =0x53000000
	ldr r1 , =0x0
	str r1 , [r0]
	
	/* 设置系统时钟 */
	/* CLKDIVN(0x4C000014) = 0X5, tFCLK:tHCLK:tPCLK = 1:4:8  */
	ldr r0, =CLKDIVN
	mov r1, #0x05
	str r1, [r0]
	
	/* 设置CPU工作于异步模式 */
	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000   //R1_nF:OR:R1_iA
	mcr p15,0,r0,c1,c0,0
	
	/* 设置MPLL, FCLK : HCLK : PCLK = 400M : 100M : 50M */
	/* 设置MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 *  m = MDIV+8 = 92+8=100
	 *  p = PDIV+2 = 1+2 = 3
	 *  s = SDIV = 1
	 *  FCLK = 2*m*Fin/(p*2^s) = 2*100*12/(3*2^1)=400M
	 */
	ldr r0, =MPLLCON
	ldr r1, =0x5c011
	str r1, [r0]

    /* 调用main函数 */
    bl main //调用main 并且保存返回地址
halt:
    b halt
