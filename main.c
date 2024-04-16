#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mat.h"
#include "stos.h"
#include "lab.h"
#include "wz.h"

int main(int argc, char **argv)
{
	time_t start, end;
    double cpu_time_used;

    start = time(NULL);
	int textorbin;
	//text --> 0
	//bin  --> 1
	FILE *in;
    if(argc > 1)
	{
		int length = strlen(argv[1]);
		char buff[4];
		if(length > 4){
            int digit = 0;
			for(int i = length-4; i < length; i++)
			{
                buff[digit] = argv[1][i];
                digit++;
			}
            buff[digit] = '\0';
			if(strcmp(buff, ".bin") == 0){
				in = fopen(argv[1], "rb");
				printf("Plik binarny otwarty\n");
				if(in == NULL) {
					fprintf(stderr, "%s: plik %s nie istnieje\n", argv[0], argv[1]);
					return 1;
				}
				textorbin = 1;
			} else {
                in = fopen(argv[1], "r");
                printf("plik txt\n");
                if(in == NULL) {
                    fprintf(stderr, "%s: plik %s nie istnieje\n", argv[0], argv[1]);
                    return 1;
                }
				textorbin = 0;
            }
		} else {
			in = fopen(argv[1], "r");
			if(in == NULL) {
                printf("plik txt\n");
				fprintf(stderr, "%s: plik %s nie istnieje\n", argv[0], argv[1]);
				return 1;
			}
			textorbin = 0;
		}
	} else {
		printf("Plik nie został podany\n");
		return 1;
	}


	FILE *out = fopen("lab.txt", "w+");
	int kk;

	lab s;
	if(textorbin == 0)
	{
		s = matt(in, out, argv[1], &kk);
	} else {
		s = mattbin(in, out, argv[1], &kk);
	}


	if(s == NULL)
	{
		fprintf(stderr, "%s: nie wczytano labirynt z pliku %s\n", argv[0], argv[1]);
		return 1;
	}
	

	
	dfs(out, s, kk);
	end = time(NULL);
    cpu_time_used = difftime(end, start);

    printf("Czas wykonania: %f sekund\n", cpu_time_used);

	free(s);
	fclose(out);
	fclose(in);
	return 0;
}
