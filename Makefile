LIBS = `pkg-config --libs gtk+-3.0`
INCLUDES = -I./include/ `pkg-config --cflags gtk+-3.0`
CC = g++
CPPFLAGS =
CXXFLAGS =
EXECUTABLE = sgi

SRC_DIR = src

SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all:	$(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)
	@echo 'Build complete!'
	@echo ' '

test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o $(EXECUTABLE)
