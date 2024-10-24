CC=gcc

CFLAGS= -I./includeDir

SRCS=./grepSources/ahoCorassic.c ./grepSources/stringArray.c ./grepSources/grep.c

OBJS= $(SRCS:.c=.o)

TARGET = grep

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) -o $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)