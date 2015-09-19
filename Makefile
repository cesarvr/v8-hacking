INCLUDE=-I/home/cesar/lab/v8Test/deps/v8
SRC=src/
COMPILER=gcc
LIBV8= -Wl,--start-group deps/v8/out/x64.release/obj.target/{tools/gyp/libv8_{base,libbase,snapshot,libplatform},third_party/icu/libicu{uc,i18n,data}}.a -Wl,--end-group
CFLAG= -lrt -ldl -lm -lpthread -std=c++0x -lstdc++ 

default: main 

main: $(SRC)main.cpp
			$(COMPILER) -Wall $(INCLUDE) $(SRC)main.cpp -o bin/main $(LIBV8)  $(CFLAG) 

clean:
			rm -r bin/main

