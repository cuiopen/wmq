#
#包含了其他makefile都用到的模式规则
#

# cross compile...
CROSS_COMPILE =

CC  = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR  = $(CROSS_COMPILE)ar

#生成的目标文件名.......
TARGET := wmq

#顶层目录
ROOT := $(shell pwd)


#需要扫描的文件
TARGET_DIRS :=src/ src/common src/tools/lzma src/tools\
				src/thread  \
				src/client  src/server\
				lib/  lib/error  \
				lib/linked-list-queue \
				lib/hashtable
			

#.h 头文件目录
INCLUDE_DIR := \
 	-I$(MAKEROOT)/inc \
	-I$(MAKEROOT)/src/common\
	-I$(MAKEROOT)/src/tools \
	-I$(MAKEROOT)/src/tools/lzma \
	-I$(MAKEROOT)/src/thread \
	-I$(MAKEROOT)/src/server\
	-I$(MAKEROOT)/src/client \
	-I$(MAKEROOT)/lib   	 \
	-I$(MAKEROOT)/lib/linked-list-queue \
	-I$(MAKEROOT)/lib/hashtable \

#lib库搜索路劲
LIB_DIR := -L$(MAKEROOT)/lib \
		   -L$(MAKEROOT)/thirdlib 
#lib库
LIB =-lpthread   

#gcc编译时定义宏
DEFINE := -D_7ZIP_ST

#gcc编译参数或者选项
CFLAGS  := $(INCLUDE_DIR)
CFLAGS  += $(DEFINE)


#优化级别 -rdynamic 打印堆栈信息中包含函数名
CFLAGS += -g -Wall -O2 -rdynamic


#对所有的.o文件以.c文件创建它
$(MAKEROOT)/obj/%.o :  %.c
	@echo "Compling: =====> " $(addsuffix .c, $(basename $(notdir $@)))
	${CC} ${CFLAGS} -c $< -o $@

$(MAKEROOT)/obj/%.o :  %.cpp
	@echo "Compling: ======> " $(addsuffix .cpp, $(basename $(notdir $@)))
	${CXX} ${CFLAGS} -c $< -o $@
