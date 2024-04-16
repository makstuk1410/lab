#include <stdio.h>
#include <stdlib.h>
#include "stos.h"
#include "mat.h"
#include "lab.h"
#include <stdint.h>
void push(wz *stos, uint16_t x, uint16_t y, uint8_t q, uint16_t waga)
{
    wz new = malloc(sizeof(struct Wezel));
    if(new == NULL)
    {
        fprintf(stderr, "niealokowana pamięć #1\n");
        return;
    }

    new->x = x;
    new->y = y;
    new->q = q;
    new->waga = waga;
    new->next = *stos;
    *stos = new;
}


void pop(wz *stos, uint16_t *x, uint16_t *y, uint8_t *q, uint16_t *waga)
{
    if(*stos == NULL)
    {
        fprintf(stderr, "Stos jest pust\n");
        return;
    }

    wz temp = *stos;
    *x = temp->x;
    *y = temp->y;
    *q = temp->q;
    *waga = temp->waga;
    *stos = temp->next;
    free(temp);
}


void freeStos(wz *stos) {
    wz temp;
    while (*stos != NULL) {
        temp = *stos;
        *stos = (*stos)->next;
        free(temp);
    }
}
