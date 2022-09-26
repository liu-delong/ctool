# 统一windows和linux
ifeq ($(OS),Windows_NT)
	Windows:=true
	rm:=-del /F /S /Q
	rm_folder:=-rd /Q /S
	path_seperator:=;
	detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
	path_seperator:=:
	Linux:=true
	rm:=-rm -rf
	rm_folder:=-rm -rf
endif

common_src:=$(wildcard src/common/*.cpp)
common_src:=$(notdir $(common_src))
common_obj:=$(patsubst %.cpp,%.o,$(common_src))
src:=$(wildcard src/*.cpp)
src:=$(notdir $(src))
obj:=$(patsubst %.cpp,%.o,$(src))
# 设置环境变量，使得源代码#include时不用指定路径
ptemp:=$(CPLUS_INCLUDE_PATH)$(path_seperator)./src/$(path_seperator)./src/common/$(path_seperator)
export CPLUS_INCLUDE_PATH=$(ptemp)
temp_path:=$(PATH)$(path_seperator)./obj
export PATH=$(temp_path)
export LIBRARY_PATH=./obj
VPATH=obj src src/common

 


# 统一windows和linux创建文件夹操作
ifeq ($(detected_OS),Windows)
	create_folder_obj:=if exist obj (mkdir abc.no.use.temp && rd abc.no.use.temp) else mkdir obj
endif

ifeq ($(detected_OS),Linux)
	create_folder_obj:=if test -d obj;then echo;else mkidr obj; fi
endif

# 自动依赖生成
depend_file:=$(patsubst %.o,%.d,$(common_obj) $(obj))
depend_file:=$(wildcard $(depend_file))

ifneq ($(depend_file),)
include $(depend_file)
endif

target:=main1
ifeq ($(detected_OS),Windows)
	target:=$(patsubst %,%.exe,$(target))
endif

# 开始定义规则

all:$(target)
 
.PHONY:all clean

main1 main1.exe:obj/main1.o $(addprefix obj/,$(common_obj))
	g++ -g $^ -o $@




obj/%.o:%.cpp
	$(shell $(create_folder_obj))
	g++ -c $^ -o $@ -MD
clean:
	$(rm) $(target) *.exe *.o *.d obj/*.o obj/*.d
# 创建obj文件夹，存放编译中间过程