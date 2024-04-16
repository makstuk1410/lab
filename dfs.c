#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lab.h"
#include "mat.h"
#include "stos.h"
#include "wz.h"


void zamianaZero(int *u)
{

    if((*u) > 47 && (*u) < 58)
    {
        (*u) -= 48;
    } else {
        (*u) = 100;
    }
}

char zamianaChar(int u)
{
    char c;
    switch(u)
    {
        case 10:
            c = '\n';
            break;
        case 32:
            c = ' ';
            break;
        case 112:
            c = 'p';
            break;
        case 115:
            c = 's';
            break;
    }

    return c;
}

void kierunek(FILE *in, lab s, int *b, uint16_t x, uint16_t y, uint8_t *q, int *sorp)
{
    //printf("kierunek\n");
    int t = (x*(s->width)+y);
    *q = 0;
    int r, l;
    

    //sprawdzamy 0 z dołu
    if(x < (s->height)-2){
        l = 0;
        fseek(in, t + (s->width), SEEK_SET);
        r = fgetc(in);
        if(r == 48)
        {
            l++;
        }

        fseek(in, t + (2*(s->width)), SEEK_SET);
        r = fgetc(in);
        if(r == 48)
        {
            l++;
        }

        if(l == 2){
            (*q)++;
            b[0] = 1;
        }

    } else if(x < (s->height)-1) {
        fseek(in, t + (s->width), SEEK_SET);
        r = fgetc(in);
        if(r == 51){
            *q = 10;
            *sorp = 1;
            b[0] = 0;
            b[1] = 0;
            b[2] = 0;
            b[3] = 0;
            return;
        }
    }
    //sprawdzamy 0 z dołu



    //sprawdzamy 0 z prawej strony
    if(y < (s->width)-2){
        l = 0;
        fseek(in, t+1, SEEK_SET);
        for(int i = 0; i < 2; i++)
        {
            r = fgetc(in);
            if(r == 48)
            {
                l++;
            }
        }

        if(l == 2)
        {
            b[1] = 1;
            (*q)++;
        }
    } else if(y < (s->width)-1) {
        fseek(in, t+1, SEEK_SET);
        r = fgetc(in);
        if(r == 51)
        {
            *q = 10;
            *sorp = 1;
            b[0] = 0;
            b[1] = 0;
            b[2] = 0;
            b[3] = 0;
            return;
        }
    }
    //sprawdzamy 0 z prawej strony



    //sprawdzenie 0 z góry
    if(x > 1){
        l = 0;
        fseek(in, t - (s->width), SEEK_SET);
        r = fgetc(in);
        if(r == 48)
        {
            l++;
        }

        fseek(in, t - (2*(s->width)), SEEK_SET);
        r = fgetc(in);
        if(r == 48)
        {
            l++;
        }

        if(l == 2){
            (*q)++;
            b[2] = 1;
        }
    } else if(x > 0) {
        fseek(in, t - (s->width), SEEK_SET);
        r = fgetc(in);
        if(r == 51)
        {
            *q = 10;
            *sorp = 1;
            b[0] = 0;
            b[1] = 0;
            b[2] = 0;
            b[3] = 0;
            return;
        }
    }
    //sprawdzenie 0 z góry


    //sprawdzenie 0 z lewej strony
    if(y > 1){
        l = 0;
        fseek(in, t-2, SEEK_SET);
        for(int i = 0; i < 2; i++)
        {
            r = fgetc(in);
            if(r == 48)
            {
                l++;
            }
        } 

        if(l == 2)
        {
            b[3] = 1;
            (*q)++;
        }
    } else if(y > 0){
        fseek(in, t - 1, SEEK_SET);
        r = fgetc(in);
        if(r == 51){
            *q = 10;
            b[0] = 0;
            b[1] = 0;
            b[2] = 0;
            b[3] = 0;
            *sorp = 1;
            return;
        }
    }
    //sprawdzenie 0 z lewej strony
    *sorp = 0;
    return;
}

void nowaSciezka(FILE *w, FILE *in, lab s, uint16_t *waga_1, int waga_s, char sym, uint16_t x, uint16_t y, int t) {
    FILE *dod = fopen("dod.txt", "w+");

    char u;
    int waga_2 = waga_s - *waga_1;
    int number;
    if(sym == 'p'){
        int start_point = ftell(w);
        fseek(w, 0, SEEK_SET);
        while(ftell(w) < start_point && u != '\n')
        {
            u = fgetc(w);
            fprintf(dod, "%c", u);

            fflush(dod);
        }
        if(ftell(w) > start_point)
        {
            fseek(w, -1, SEEK_CUR);
        }
        for(int i = 0; i < *waga_1; i++)
        {
            u = fgetc(w);
            fprintf(dod, "%c", u);
            fflush(dod);
        }

        for(int i = 0; i < waga_2; i++)
        {
            u = fgetc(w);
            number = u - '0';
            zamiana(in, number, s, &x, &y, 0, t);   
        }

        fclose(w);
        w = fopen("sciezki.txt", "w+");

        fseek(dod, 0, SEEK_SET);
        while((u = fgetc(dod)) != -1)
        {
            fprintf(w, "%c", u);
            fflush(w);
        }
    } else {
        for(int i = 0; i < *waga_1; i++)
        {
            u = fgetc(w);
            fprintf(dod, "%c", u);
            fflush(dod);
        }
        for(int i = 0; i < waga_2; i++)
        {
            u = fgetc(w);
            number = u - '0';
            zamiana(in, number, s, &x, &y, 0, t);   
        }
        fseek(w, 0, SEEK_END);
        fprintf(w, " %c %d\n", sym, waga_s);
        fseek(dod, 0, SEEK_SET);
        while((u = fgetc(dod)) != EOF)
        {
            fprintf(w, "%c", u);
            fflush(w);
        }
    }
    fseek(w, 0, SEEK_END);
    fclose(dod);

}



void zamiana(FILE* in, int k, lab s, uint16_t *x, uint16_t *y, int num, int t){
    //printf("zamiana\n");
    t = (*x)*(s->width) + (*y);
    fseek(in, t, SEEK_SET);
    fprintf(in, "%d", num);
    switch(k)
    {
        case 0:
            fseek(in, t + (s->width), SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            fseek(in, t + (2*(s->width)), SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            *x += 2;
            break;
        case 1:
            fseek(in, t + 1, SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            fseek(in, t + 2, SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            *y += 2;
            break;
        case 2:
            fseek(in, t - (s->width), SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            fseek(in, t - (2*(s->width)), SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            *x -= 2;
            break;
        case 3:
            fseek(in, t - 1, SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            fseek(in, t - 2, SEEK_SET);
            fprintf(in, "%d", num);
            fflush(in);
            *y -= 2;
            break;
    }
}


void ruch(FILE *in, FILE *w, wz *ww, lab s, uint16_t *x, uint16_t *y, uint8_t q, uint16_t *waga, int kk)
{
    //printf("ruch 1\n");
    int sorp = 0;
    int b[4] = {0, 0, 0, 0};
    //printf("ruchuj\n");
    if(q == 11){
        //printf("ruchuj1\n");
        kierunek(in, s, b, *x, *y, &q, &sorp);
    } else if(q == 20){
        ////printf("ruchuj2\n");
        q = 1;
        b[0] = 1;
    } else if(q == 21){
        //printf("ruchuj3\n");
        q = 1;
        b[1] = 1;
    } else if(q == 22) {
        //printf("ruchuj4\n");
        q = 1;
        b[2] = 1;
    } else if(q == 23) {
        //printf("ruchuj5\n");
        q = 1;
        b[3] = 1;
    }
    
    int k, waga1, t;
    //printf("ruchuj6\n");
    char ma;
    //printf("ruchuj7\n");
    int jj, u1, u2;
    //printf("ruchhh\n");
    switch(q)
    {
        //znaleziona ścieżka
        case 10:
            //printf("ruch 2\n");
            if(*ww == NULL)
            {
                printf("START\n");
                fseek(w, 0, SEEK_END);
                if(sorp == 0)
                {
                    fprintf(w, " p %d", *waga);
                } else {
                    fprintf(w, " s %d", *waga);
                }
                fseek(w, 0, SEEK_SET);
                int c1;
                char b1;
                int wm = INT_MAX;
                while(fscanf(w, "%*d %c %d", &b1, &c1) == 2)
                {

                    if(b1 == 's')
                    {
                        if(c1 < wm)
                        {
                            wm = c1;
                        }
                    }
                }
                //printf("okk\n");
                fseek(w, 0, SEEK_SET);
                while(fscanf(w, "%*d %c %d", &b1, &c1) == 2)
                {
                    if(b1 == 's' && c1 == wm)
                    {
                        fseek(w, -1, SEEK_CUR);
                        int u;
                        while((u = fgetc(w)) != 10 && ftell(w) != 1)
                        {
                            fseek(w, -2, SEEK_CUR);
                        }
                        if(ftell(w) == 1)
                        {
                            fseek(w, 0, SEEK_SET);
                        }
                        u2 = kk;
                        jj = 1;
                        *x = (s->start).x;
                        *y = (s->start).y;
                        
                        for(int i = 0; i < wm+1; i++)
                        {
                            
                            
                            if(i == wm){
                                u1 = kk;
                                if(u1 == u2)
                                {
                                    jj++;
                                    printf("FORWARD %d\n", jj);
                                    break;
                                }
                            } else {
                                u1 = fgetc(w);
                                zamianaZero(&u1);
                                t = 0;
                                zamiana(in, u1, s, x, y, 3, t);
                            }
                            
                            if(u1 == u2)
                            {
                                jj += 2;
                            } else {
                                printf("FORWARD %d\n", jj);
                                switch(u2){
                                    case 0:
                                        if(u1 == 3)
                                            printf("TURNRIGHT\n");
                                        else
                                            printf("TURNLEFT\n");
                                        break;
                                    case 1:
                                        if(u1 == 0)
                                            printf("TURNRIGHT\n");
                                        else
                                            printf("TURNLEFT\n");
                                        break;
                                    case 2:
                                        if(u1 == 1)
                                            printf("TURNRIGHT\n");
                                        else
                                            printf("TURNLEFT\n");
                                        break;
                                    case 3:
                                        if(u1 == 2)
                                            printf("TURNRIGHT\n");
                                        else
                                            printf("TURNLEFT\n");
                                        break;
                                }
                                if(i == wm){
                                    printf("FORWARD 1\n");
                                }
                                u2 = u1;
                                jj = 2;
                            }
                        }
                        
                        printf("STOP\n");
                        FILE *wej = fopen("wejscie.txt", "w+");
                        fseek(in, 0, SEEK_SET);
                        for(int lj = 0; lj < s->height; lj++)
                        {
                            for(int lj = 0; lj < s->width; lj++)
                            {
                                char symc = fgetc(in);
                                fprintf(wej, "%c", symc);
                            }
                            fprintf(wej, "\n");
                        }
                        return;
                    }
                }
            } else {
                waga1 = *waga;
                fseek(w, -waga1, SEEK_END);
                pop(ww, x, y, &q, waga);
                q += 20;
                t = ((*x)*(s->width))+(*y);
                nowaSciezka(w, in, s, waga, waga1, 's', *x, *y, t);
                ruch(in, w, ww, s, x, y, q, waga, kk);
            }
            break;

        

        //przeszkoda
        case 0:
            //printf("ruch 3\n");
            waga1 = *waga;
            //printf("%d\n", waga1);
            fseek(w, -waga1, SEEK_CUR);
            if(*ww != NULL)
            {
                pop(ww, x, y, &q, waga);
            } else {
                ruch(in, w, ww, s, x, y, 10, waga, kk);
                return; 
            }
            q += 20;
            ma = 'p';
            t = ((*x)*(s->width))+(*y);
            nowaSciezka(w, in, s, waga, waga1, ma, *x, *y, t);
            ruch(in, w, ww, s, x, y, q, waga, kk);
            break;



        //tylko jeden kierunek
        case 1:
            //printf("ruch 4\n");
            t = ((*x)*(s->width))+(*y);
            for(int i = 0; i < 4; i++)
            {
                if(b[i] == 1)
                {
                    k = i;
                }
            }

            zamiana(in, k, s, x, y, 2, t);
            fseek(w, 0, SEEK_END);
            fprintf(w, "%d", k);
            fflush(w);
            (*waga)++;
            ruch(in, w, ww, s, x, y, 11, waga, kk);
            break;


        //istnieje węzeł
        default:
            for(int i = 3; i >= 0; i--)
            {
                if(b[i] == 1)
                {
                    push(ww, *x, *y, i, *waga);
                }
            }
            pop(ww, x, y, &q, waga);
            q +=20;
            ruch(in, w, ww, s, x, y, q, waga, kk);
            break;
    }
}


void dfs(FILE *in, lab s, int kk)
{
    uint16_t x = (s->start).x;
    uint16_t y = (s->start).y;
    wz w = NULL;
    FILE *sc = fopen("sciezki.txt", "w+");

    uint16_t waga = 0;
    ruch(in, sc, &w, s, &x, &y, 11, &waga, kk);
    fclose(sc);
}