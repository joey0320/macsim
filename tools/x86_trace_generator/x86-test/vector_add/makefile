CC=g++
CFLAGS += -g
LIBS=-lpthread

add: add.o
		    $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
		    $(CC) $(CFLAGS) -c -o $@ $^

clean:
		    rm *.o add
