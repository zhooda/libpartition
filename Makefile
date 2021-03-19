CC=clang
AR=ar
CFLAGS=-Wall
OBJS=partition.o partition.h
LIB=./build/libpartition.a

all: $(LIB) clean

test: test/main.c $(LIB)
	$(CC) $^ -o test/main && ./test/main 

$(LIB): $(OBJS)
	$(AR) rcs $@ $^
	cp partition.h build/partition.h

%.o: %.c
	$(CC) -c -o $@ $^

clean:
	rm *.o