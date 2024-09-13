CC=gcc
CFLAGS=-g
BINS=asyncIO syncIO

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ -lrt

clean:
	rm -rf *.dSYM $(BINS)