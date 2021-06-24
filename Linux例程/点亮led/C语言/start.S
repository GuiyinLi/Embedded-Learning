.text
.global _start

_start:
	ldr r0 , =0x53000000
	ldr r1 , =0x8021
	str r1 , [r0]
    /* 设置内存 堆栈指针寄存器 SP */
    ldr sp, = 4096 //片内SDRAM前4K字节的顶部 Nand启动 
    //ldr sp, =0x40000000+4096 //Nor启动 0地址对应Nor Flash
    
    /* 调用main函数 */
    bl main //调用main 并且保存返回地址
halt:
    b halt
