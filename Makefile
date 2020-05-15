SRC := $(shell find src/ -name "*.c")
CC ?= gcc

all: $(SRC:.c=.o)

%.o: %.c
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -vf src/*.o
