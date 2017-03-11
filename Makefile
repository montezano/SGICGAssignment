LIBS = `pkg-config --libs gtk+-3.0`
INCLUDES = -I./include/ `pkg-config --cflags gtk+-3.0`
CC = g++ -std=c++11
CPPFLAGS =
CXXFLAGS =
EXECUTABLE = sgi

SRC_DIR = src
SRC_VIEW_DIR = src/view
SRC_CONTR_DIR = src/controller


SRCS += $(wildcard $(SRC_DIR)/*.cpp)
SRCS += $(wildcard $(SRC_VIEW_DIR)/*.cpp)
SRCS += $(wildcard $(SRC_CONTR_DIR)/*.cpp)
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
	rm -rf ./$(SRC_VIEW_DIR)/*.o
	rm -rf ./$(SRC_CONTR_DIR)/*.o
