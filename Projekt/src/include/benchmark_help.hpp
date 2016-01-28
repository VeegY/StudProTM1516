#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>

void random_ints(int *data,int *indices, int* fvec, int dim)
{
	for (int i = 0; i < dim;i++)
	{ 
  //Fuelle Reihe
        int entries_row=rand()%dim; //0-DIM Eintraege pro Reihe B: dim 4  entries_row =3
        int place_current; //der zu setzende Index zwischen 
        int place_old=0; // Index Postition vom Wert davor
        int range; //Reichweite fuer den Zufall
        for (int j = 0; j < dim; j++)
        {
	        //Fuelle i-te Stelle der Reihe
	        if (j < entries_row)  //entries row 3
	        {
		        data[j*dim+i] = rand() % 10;  //passt
		        range = dim - (entries_row - j) - place_old + 1;
		        place_current = (rand() % range) + place_old;
		        indices[j*dim+i] = place_current;
		        place_old = place_current+1;
	        }
	        else
	        {
		        data[j*dim+i] = 0;
		        indices[j*dim+i] = 0; 
	        }

        }
		fvec[i] = rand() % 10;
    }
}

bool check_result(int *result, int *datah, int *indicesh, int *fvech, int dim)
{
    //bool check = true;
    for (int i = 0; i < dim; i++)
    {
        int value = 0;
        for (int j = 0; j < dim; j++)
        {
            value += datah[j*dim+i] * fvech[indicesh[j*dim+i]];
        }
        if (value != result[i])
        {
            return false;
        }
    }
    return true;
}

void set_values(int *datah, int *indicesh, int *fvech, int *datag, int *indicesg, int *fvecg, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			datag[i*dim + j] = datah[i*dim + j];
			indicesg[i*dim + j] = indicesh[i*dim + j];
		}
		fvecg[i] = fvech[i];
	}
}

void print_time(float *ukt, float *uot, float *zkt, float *zot,int runs)
{
    float uktime=0, uotime=0, zktime=0, zotime=0;
    for(int n=0;n<runs;n++)
    {
      uktime += ukt[n];
      uotime += uot[n];
      zktime += zkt[n];
      zotime += zot[n];
    }
    uktime = (uktime/runs)*1000;
    uotime = (uotime/runs)*1000;
    zktime = (zktime/runs)*1000;
    zotime = (zotime/runs)*1000;

    printf("UK: %fms - UO: %fms - ZK: %fms - ZO: %fms\n",uktime,uotime,zktime,zotime);
}

void print_stuff(int *data, int *indices, int *fvec,int *result,  int dim)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			printf("%i:%i - ", data[i*dim + j], indices[i*dim + j]);
		}
		printf(" --- vec: %i ~~~> Result: %i\n", fvec[i],result[i]);
	}
}
