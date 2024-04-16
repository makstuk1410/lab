#ifndef _WZ_H_
#define _WZ_H_

#include <stdint.h>

typedef struct Wezel {
    uint16_t x;
    uint16_t y;
    uint8_t q;
    uint16_t waga;
    struct Wezel *next;
} *wz;


#endif