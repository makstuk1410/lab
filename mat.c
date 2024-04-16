#include "mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//0 --> 48
//1 --> 49
//2 --> 50



int startPunktt(FILE *in, lab s)
{
	int x = (s->start).x;
	int y = (s->start).y;
    int t = ((x)*(s->width)+(y));
	int r;
	int q = -1;


    //sprawdzamy 0 z dołu
    if((x) < (s->height)-1){
        fseek(in, t + (s->width), SEEK_SET);
        if((r = fgetc(in)) == 48)
        {
			((s->start).x)++;
			q = 0;
			return q;
        }
    }
    //sprawdzamy 0 z dołu



    //sprawdzamy 0 z prawej strony
    if((y) < (s->width)-1){
        fseek(in, t+1, SEEK_SET);
		if((r = fgetc(in)) == 48)
		{
			((s->start).y)++;
			q = 1;
			return q;
		}
    }
    //sprawdzamy 0 z prawej strony



    //sprawdzenie 0 z góry
    if((x) > 0){
        fseek(in, t - (s->width), SEEK_SET);
        if((r = fgetc(in)) == 48)
        {
            ((s->start).x)--;
			q = 2;
			return q;
        }
    }
    //sprawdzenie 0 z góry



    //sprawdzenie 0 z lewej strony
    if((y) > 0){
        fseek(in, t-1, SEEK_SET);
		if((r = fgetc(in)) == 48)
		{
			((s->start).y)--;
			q = 3;
			return q;
		}
    }
	return q;
    //sprawdzenie 0 z lewej strony
}

lab matt(FILE *in, FILE *out, char *plik, int* kk)
{
	int const_width = 0;
	int width = 0;
	int height = 1;
	char temp;
	
	while((temp = fgetc(in)) != EOF)
	{
		if(temp == '\n')
		{
			if(height == 1)
			{
				const_width = width;
			}
			height++;
			if(width != const_width)
			{
				fprintf(stderr, "Nie poprawny format labiryntu w pliku \"%s\"\n Nie możliwe czytanie takiego labiryntu\n", plik);
				return NULL;
			}
			width = 0;
			continue;
		}
		width++;
	}
	height--;

	lab new = malloc(sizeof(lab));
	if(new == NULL) 
	{
		fprintf(stderr, "Błąd alokowania pamięci\n");
		return NULL;
	}
	
	new->height = height;
	new->width = const_width;
	
	fseek(in, 0, SEEK_SET);
	int x = 0;
	int y = 0;
	while((temp = getc(in)) != EOF)
	{
		int ff;
		switch(temp)
		{

			case '\n':
				y = 0;
				x++;
				break;
			case 'X':
				ff = 1;
				fprintf(out, "%d", ff);
				y++;
				break;
			case ' ':
				ff = 0;
				fprintf(out, "%d", ff);
				y++;
				break;
			case 'P':
				ff = 2;
				(new->start).x = x;
				(new->start).y = y;
				fprintf(out, "%d", ff);
				y++;
				break;
			case 'K':
				ff = 3;
				(new->finish).x = x;
				(new->finish).y = y;
				fprintf(out, "%d", ff);
				y++;
				break;
			default:
				free(new);
				fprintf(stderr, "Bzdura w pliku: %c\n", temp);
				return NULL;
				break;
		}
	}

	*kk = startPunktt(out, new);


	printf("Start: %d %d\n", (new->start).x, (new->start).y);
	printf("Width/height: %d %d\n", new->width, new->height);
	return new;
}



lab mattbin(FILE *in, FILE *out, char *plik, int* kk)
{
	lab new = malloc(sizeof(lab));
	if(new == NULL) 
	{
		fprintf(stderr, "Błąd alokowania pamięci\n");
		return NULL;
	}


	fseek(in, 5, SEEK_SET);
    uint16_t kol;

    fread(&kol, sizeof(uint16_t), 1, in);
	new->width = (int)kol;

    fread(&kol, sizeof(uint16_t), 1, in);
    new->height = (int)kol;

    fread(&kol, sizeof(uint16_t), 1, in);
    (new->start).y = ((int)kol)-1;

    fread(&kol, sizeof(uint16_t), 1, in);
    (new->start).x = ((int)kol)-1;

    fread(&kol, sizeof(uint16_t), 1, in);
    (new->finish).y = ((int)kol)-1;

    fread(&kol, sizeof(uint16_t), 1, in);
    (new->finish).x = ((int)kol)-1;


        uint8_t sep;
    fseek(in, 37, SEEK_SET);
    fread(&sep, sizeof(uint8_t), 1, in);
	int separator = (int)sep;

    fread(&sep, sizeof(uint8_t), 1, in);
    int wall = (int)sep;

    fread(&sep, sizeof(uint8_t), 1, in);
    int path = (int)sep;


	fseek(in, 40, SEEK_SET);
    int ex, hei, wid;
    hei = 0;
    wid = 0;
    while(hei < new->height)
    {
        uint8_t s;
		int ff;
        fread(&s, sizeof(uint8_t), 1, in);
        ex = (int)s;
		if(ex == separator){
			continue;
		} else if(ex == wall){
			fread(&s, sizeof(uint8_t), 1, in);
			for(int j = wid; j < wid+((int)s)+1; j++)
			{
				ff = 1;
				fprintf(out, "%d", ff);
			}
			wid += (int)s;
			wid++;
			if(wid > new->height-1){ 
				wid -= new->height; 
				hei++;
			}
		} else if(ex == path) {
			fread(&s, sizeof(uint8_t), 1, in);
			for(int j = wid; j < wid+((int)s) +1; j++)
			{
				ff = 0;
				fprintf(out, "%d", ff);
			}
			wid += (int)s;
			wid++;
			if(wid > new->height-1){
				wid -= new->height;
				hei++;
			}
		} else {
			free(new);
			fprintf(stderr, "Bzdura w pliku: %d\n", ex);
			return NULL;
		}
    }   
	fflush(out);
	fseek(out, (new->start).x * new->width + (new->start).y, SEEK_SET);
	fprintf(out, "%d", 2);

	fseek(out, (new->finish).x * new->width + (new->finish).y, SEEK_SET);
	fprintf(out, "%d", 3);
	printf("Start: %d %d\n", (new->start).x, (new->start).y);
	*kk = startPunktt(out, new);
	fflush(out);
	printf("Start: %d %d\n", (new->start).x, (new->start).y);
	printf("Width/height: %d %d\n", new->width, new->height);
	return new;
}