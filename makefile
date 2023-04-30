CC = gcc
LIBS = -lm

all: cmp copy encode decode stshell

stshell: stshell.o
	$(CC) stshell.o -o stshell

cmp: cmp.o
	$(CC) cmp.o -o cmp

copy: copy.o
	$(CC) copy.o -o copy

encode: encode.o libcodecA.so libcodecB.so
	$(CC) encode.o -L. -lcodecA -lcodecB -o encode $(LIBS)

decode: decode.o libcodecA.so libcodecB.so
	$(CC) decode.o -L. -lcodecA -lcodecB -o decode $(LIBS)

libcodecA.so: codecA.o
	$(CC) $(CFLAGS) -shared -o libcodecA.so codecA.o

libcodecB.so: codecB.o
	$(CC) $(CFLAGS) -shared -o libcodecB.so codecB.o

stshell.o: stshell.c
	$(CC) -c stshell.c

cmp.o: cmp.c
	$(CC) -c cmp.c

copy.o: copy.c
	$(CC) -c copy.c

encode.o: encode.c
	$(CC) -c encode.c

decode.o: decode.c
	$(CC) -c decode.c

codecA.o: codecA.c
	$(CC) -c -fPIC codecA.c

codecB.o: codecB.c
	$(CC) -c -fPIC codecB.c

clean:
	rm -f *.o *.so cmp copy encode decode stshell
