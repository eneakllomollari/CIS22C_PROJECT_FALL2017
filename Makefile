CC := g++
SOURCES := main.cpp
OBJS := $(SOURCES:.cpp=.o)
all: main
main: $(OBJS)
	@$(CC) -o main $(OBJS)
	@./main
	@rm -rf main.o main
.SILENT:main
