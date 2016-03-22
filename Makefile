# define the compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -std=c++11 -Wall -g

# define any directories containing header files other than /usr/include
INCLUDES =

# define library paths in addition to /usr/lib
LFLAGS =

# define any libraries to link into executable
LIBS =

# define the C++ source files
SRCS = CircularList.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

# define the executable file
MAIN = compiler

all:    $(MAIN)

$(MAIN): $(OBJS)
        $(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

main.o: main.cpp CircularList.hpp
        $(CC) $(CFLAGS) $(INCLUDES) -c main.cpp


# Phony targets
.PHONY: clean
clean:
        $(RM) *.o *~ $(MAIN)
