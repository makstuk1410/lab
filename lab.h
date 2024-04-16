#ifndef _LAB_H_
#define _LAB_H_

#include <stdio.h>
#include <stdlib.h>
#include "mat.h"
#include "stos.h"
#include "wz.h"


void kierunek(FILE *in, lab s, int *b, uint16_t x, uint16_t y, uint8_t *q, int *sorp);
void nowaSciezka(FILE *w, FILE *in, lab s, uint16_t *waga_1, int waga_s, char sym, uint16_t x, uint16_t y, int t);
void zamiana(FILE* in, int k, lab s, uint16_t *x, uint16_t *y, int num, int t);
void ruch(FILE *in, FILE *w, wz *ww, lab s, uint16_t *x, uint16_t *y, uint8_t q, uint16_t *waga, int kk);
void dfs(FILE *in, lab s, int kk);

double ocenaKosztu(int waga, int x, int y, lab s);
void kierunekAstar(FILE *in, lab s, int *b, int x, int y, int *q, int *sorp, int waga);
void ruchAstar(FILE *in, FILE *w, wz *ww, lab s, int *x, int *y, int q, int *waga, int kk);
void astar(FILE *in, lab s, int kk);

void kierunekPr(FILE *in, lab s, int *b, int x, int y, int *q, int *sorp);
void ruchPr(FILE *in, FILE *w, wz *ww, lab s, int *x, int *y, int q, int *waga, int kk);
void prawareka(FILE *in, lab s, int kk);

#endif