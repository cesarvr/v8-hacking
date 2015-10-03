SRC=src/
CC=gcc
LIBV8= -Wl,--start-group deps/v8/out/x64.release/obj.target/{tools/gyp/libv8_{base,libbase,snapshot,libplatform},third_party/icu/libicu{uc,i18n,data}}.a -Wl,--end-group
CFLAG= -lrt -ldl -lm -pthread -std=c++0x -lstdc++ 
DEPS = $(SRC)include/
INCLUDE=-I/home/cesar/lab/v8Test/deps/v8

default: main 

	

main: tools.o $(SRC)native.cpp 			
			$(CC) tools.o -Wall $(INCLUDE) -I$(DEPS) $(SRC)native.cpp -o bin/native $(LIBV8) $(CFLAG) 
			chmod +x bin/native

tools.o: $(DEPS)tools.c $(DEPS)tools.h
				$(CC) -c $(DEPS)tools.c -o tools.o
	
clean:
			rm -r bin/*


hello: $(SRC)main.cpp
			$(CC) -Wall $(INCLUDE) $(SRC)main.cpp -o bin/main $(LIBV8) $(CFLAG) 
			chmod +x bin/main



