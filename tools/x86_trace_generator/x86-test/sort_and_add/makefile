CC=g++
CFLAGS += -Wall -Wextra -Wwrite-strings -Wno-parentheses -Wpedantic -Warray-bounds
CFLAGS += -g
LDFLAGS=
LIBS=

main: main.o 
		    $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
		    $(CC) $(CFLAGS) -c -o $@ $^

clean:
		    rm *.o main
