#ifndef _MAT_H_IS_INCLUDED_
#define _MAT_H_IS_INCLUDED_

#include <stdio.h>
#include <stdlib.h>

typedef struct elem {
	int x;
	int y;	
} elem;


typedef struct lab {
	int width;
	int height;
	elem start;
	elem finish;
} *lab;

lab matt(FILE *in, FILE *out, char *plik, int* kk);
int startPunktt(FILE *in, lab s);
lab mattbin(FILE *in, FILE *out, char *plik, int* kk);


#endif
