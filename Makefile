CFLAGS = -Wall -g
LDFLAGS = -lm


all: final

final: main.o mat.o lab.o stos.o
	gcc $(CLFAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c mat.h mat.h lab.h stos.h wz.h
	gcc $(CFLAGS) -c -o $@ $<

mat.o: mat.c mat.h 
	gcc $(CFLAGS) -c -o $@ $<

lab.o: dfs.c lab.h mat.h wz.h stos.c stos.h 
	gcc $(CFLAGS) -c -o $@ $<

stos.o: stos.c wz.h stos.h
	gcc $(CFLAGS) -c -o $@ $<

clean: 
	rm -f *.o final