srcs := $(wildcard *.c)   #源文件
objs := $(srcs:%.c=.%.o)  #目标文件
defs := $(srcs:%.c=.%.d)  #依赖文件

#CFLAGS是用来定义编译器的编译选项   Werror:将warning提示为error -I指定头文件路径
CFLASS = -Werror -Iinclude  

test: $(objs)
	gcc -o test $^

#以下代码的作用是判断是否包含头文件(依赖文件) 当更改某个.h后，保证Makefile会重新生成目标文件和可执行程序
-include $(defs)    #忽略由于.d不存在而产生的错误 继续生成.d文件
#在编译程序的时候 生成隐藏的依赖文件  删除临时产生的.d文件
.%.o: %.c
	gcc $(CFLASS) -c -o $@ $< -MD -MF .$*.d
clean:  #删除所有的依赖文件
	rm test $(objs)
distclean:                    #删除所有的依赖文件
	rm $(defs)
.PHONY: clean test distclean
