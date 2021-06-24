.text
.global _start

_start:
	/* 关闭看门狗 */
	ldr r0 , =0x53000000
	ldr r1 , =0x0
	str r1 , [r0]
	
	/* 设置MPLL  FCLK : HCLK : PCLK = 400M : 100M : 50M */
	/* LOCKTIME(0x4C000000) = 0xFFFFFFFF */
	ldr r0 , = 0x4C000000
	ldr r1 , = 0xFFFFFFFF
	str r1 , [r0]
	
	/* CLKDIVN(0x4C000014) = 0X5  FCLK : HCLK : PCLK = 1 : 4 : 8 */
	ldr r0 , = 0x4C000014
	ldr r1 , = 0X5
	str r1 , [r0]
	
	/* 设置CPU工作于异步模式 */
	mrc p15,0,r0,c1,c0,0       
	orr r0,r0,#0xc0000000 
	mcr p15,0,r0,c1,c0,0

	/* MPLLCON(0x4C000004) = (92<<12)|(1<<4)|(1<<0) 
	 * m = MDIV+8 = 92+8 = 100
	 * p = PDIV+2 = 1+2 =3
	 * S = SDIV = 1
	 * FCLK = 2*m*FIV/(p*2^s) = (2*100*12)/(3*2) = 400MHz
	 */
	ldr r0 , = 0x4C000004
	ldr r1 , = 0X5
	str r1 , [r0]
	/* 一旦设置PLL，就会锁定lock time直到PLL输出稳定，然后CPU工作于新的频率 */
	
	/*自动分辨是nor/nand启动 
	 *写0到0地址，再读出来
	 *如果读取到的值是0，表示0地址上的内容被修改了，它对应ram，这就是nand启动
	 *否则为nor启动
	 */
	 mov r1 , #0
	 ldr r0 , [r1] //读取0地址的值进行备份
	 str r1 , [r1] //0->[0] 将0写入0地址
	 ldr r2 , [r1] //r2=[0]将0地址的数据读取出来，存放到r2中
	 cmp r1 ,r2 //比较r1 r2 比较写入值和读取值是否相同
	 ldr sp, =0x40000000+4096
	 moveq sp , #4096 //如果r1 r2相同 则sp=4096
	 streq r0 , [r1] //恢复原来的值
	 
    
    /* 调用main函数 */
    bl main //调用main 并且保存返回地址
halt:
    b halt
