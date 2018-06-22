#c compiler
CC = g++

# define c++ compiler flags
CFLAGS =-g -Wall $(SDL2CFLAGS)

#define library paths
LFLAGS = -L"/usr/lib/x86_64-linux-gnu" 

#define library names
LIBS = -lSDL2 -lSDL2_ttf -lm -lpthread

#define SDL2 Options
SDL2CFLAGS = -D_REENRRANT
SDL2INCLUDES = -I/usr/include/SDL2 

#define include directories
INCLUDES =-I../include $(SDL2INCLUDES) -I../libv4l/include

#define object files
OBJS = $(SRCS:.cpp=.o)

# define the C source files

SRCS = main.cpp display.cpp

# define the executable file 
MAIN = ../bin/test

# add .cu suffix so we can compile cuda files
.SUFFIXES :.cu .cpp

.PHONY:all 

all:$(MAIN) clean


$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(INCLUDES) $(LFLAGS) $(LIBS) $(SDLCONF)

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

clean:
	rm *.o
