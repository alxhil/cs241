PROGRAMS=cipher testlcg
CFLAGS= -Wall -ansi -pedantic

all: $(PROGRAMS)

cipher: cipher.c lcg.c lcg.h 
	gcc $(CFLAGS) -g -o cipher cipher.c lcg.c

testlcg: testlcg.c lcg.c lcg.h 
	gcc $(CFLAGS) -g -o testlcg testlcg.c lcg.c

clean:
	-rm $(PROGRAMS)


