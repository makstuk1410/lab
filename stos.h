#ifndef _STOS_H_
#define _STOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lab.h"
#include "mat.h"
#include "wz.h"

void push(wz *stos, uint16_t x, uint16_t y, uint8_t q, uint16_t waga);
void pop(wz *stos, uint16_t *x, uint16_t *y, uint8_t *q, uint16_t *waga);
void freeStos(wz *stos);

#endif