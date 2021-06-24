dir := a b c d Makefile
files := $(foreach dir_temp,$(dir),$(wildcard $(dir_temp)/*))
filter_file = $(filter %.c %.s , $(wildcard a/* ))
result = $(patsubst abc,cba,abc defg) 
all:
	@echo dirs = $(dir)
	@echo files = $(files)
	@echo filter_file = $(filter_file)
	@echo result = $(result)
	