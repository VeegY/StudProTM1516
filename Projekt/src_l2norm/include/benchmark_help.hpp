#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#define WARNING "\e[30;41;1m"
#define GREEN "\e[32;1m"
#define RESET "\e[0m"

void diagonal_float(float *data, int *indices, float *fvec, int max_row_length, int dim_local, int dim_fvec)
{
    srand(static_cast <unsigned> (time(0)));
    int diag[7];
    diag[0] = -floor(pow(dim_local, (2.0/3.0)));
    diag[1] = -floor(pow(dim_local, (1.0/3.0)));
    diag[2] = -1;
    diag[3] = 0;
    diag[4] = 1;
    diag[5] = floor(pow(dim_local, (1.0/3.0)));
    diag[6] = floor(pow(dim_local, (2.0/3.0)));

    for (int i = 0; i < dim_local;i++)
    {
        int offset=0;
        for (int j = 0; j < max_row_length; j++)
        {
            float value = 0;
            if (diag[j] >= 0 && diag[j] < dim_local)
            {
                value = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
                data[i+offset*dim_local] = value;
                indices[i+offset*dim_local] = diag[j];
                offset++;
            }
        diag[j] = diag[j]+1;

        }
        for (int off = offset; off < max_row_length; off++)
        {
            data[i+offset*dim_local] = 0;
            indices[i+offset*dim_local] = 0;
        }


    }
    for (int k = 0; k < dim_fvec; k++)
    {
        fvec[k]= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
    }

}

void vec_float(float *vecone, float* vectwo, int dim_local)
{
    srand(static_cast <unsigned> (time(0)));
    float value_one, value_two;
    for (int k = 0; k < dim_local; k++)
    {
        value_one = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
        value_two = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100));
        vecone[k] = value_one;
        vectwo[k] = value_two;
    }

}

void vec_float_one(float *vecone, int dim_local)
{
    srand(static_cast <unsigned> (time(0)));
    float value_one;
    for (int k = 0; k < dim_local; k++)
    {
        value_one = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10));
        vecone[k] = value_one;
    }

}

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

void check_result(float *result, float *datah, int *indicesh, float *fvech, int max_row_length, int dim_local, char a)
{
    bool check = true;
    for (int i = 0; i < dim_local; i++)
    {
        float value = 0.0;
        for (int j = 0; j < max_row_length; j++)
        {
            value += datah[i+dim_local*j] * fvech[indicesh[i+dim_local*j]];
        }
        float diff = value - result[i];
        if (diff > 1.0e-2 || diff < -1.0e-2)
        {
            check = false;
        }
    }
    if(check)
    {
        printf(GREEN "%c_Kernel outcome true\n" RESET, a);
    }
    else printf(WARNING "%c_Kernel outcome false\n", a);
}

void check_result_dotproduct(float *result, float *veconeh, float *vectwoh, int dim_local, char a)
{
    float diff, value = 0.0;
    bool check = true;
    for (int k = 0; k < dim_local; k++)
    {
        value += veconeh[k] * vectwoh[k];
    }
    diff = value - result[0];
    printf("DIFF: %f\nVALUE: %f\nRESULT: %f\n", diff, value, result);
    if (diff > 1.0e-2 || diff < -1.0e-2)
    {
        check = false;
    }

    if (check)
    {
        printf(GREEN "%c_Kernel outcome true\n" RESET, a);
    }
    else printf(WARNING "%c_Kernel outcome false\n", a);
}

void check_result_l2norm(float *result, float *vectwoh, int dim_local, char a)
{
    float diff, value = 0.0;
    bool check = true;
    for (int k = 0; k < dim_local; k++)
    {
        value += vectwoh[k] * vectwoh[k];
    }
    diff = sqrt(value) - result[0];
    printf(GREEN "DIFF: %f\nVALUE: %f\nRESULT: %f\n" RESET, diff, value, result);
    if (diff > 1.0e-2 || diff < -1.0e-2)
    {
        check = false;
    }

    if (check)
    {
        printf(GREEN "%c_Kernel outcome true\n" RESET, a);
    }
    else printf(WARNING "%c_Kernel outcome false\n", a);
}

void set_values(float *datah, int *indicesh, float *fvech, float *datag, int *indicesg, float *fvecg, int max_row_length, int dim_local, int dim_fvec)
{
	for (int i = 0; i < dim_local; i++)
	{
		for (int j = 0; j < max_row_length;j++)
		{
			datag[j*dim_local+i] = datah[j*dim_local + i];
			indicesg[j*dim_local + i] = indicesh[j*dim_local + i];
		}
	}
    for (int k = 0; k < dim_fvec; k++)
    {
        fvecg[k] = fvech[k];
    }
}

void set_values(float *veconeh, float *vectwoh, float *veconeg, float *vectwog, int dim_local)
{
    for (int k = 0; k < dim_local; k++)
    {
        veconeg[k] = veconeh[k];
        vectwog[k] = vectwoh[k];
    }
}

void set_values_l2norm(float *veconeh, float *veconeg, int dim_local)
{
    for (int k = 0; k < dim_local; k++)
    {
        veconeg[k] = veconeh[k];
    }
}

void print_vec(float *vecone, float *vectwo, int dim_local)
{
    for (int k = 0; k < dim_local; k++)
    {
        printf("Vector One: %f ~~ Vector Two: %f\n", vecone[k], vectwo[k]);
    }
}

void print_vec_one(float *vecone, int dim_local)
{
    for (int k = 0; k < dim_local; k++)
    {
        printf("Vector One: %f\n", vecone[k]);
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

void print_stuff(float *data, int *indices, float *fvec, float *result,  int max_row_length, int dim_local, int dim_fvec)
{
	for (int i = 0; i < dim_local; i++)
	{
		for (int j = 0; j < max_row_length; j++)
		{
			printf("%f:%i - ", data[dim_local*j+i], indices[dim_local*j+i]);
		}
		printf(" --- vec: %f ~~~> Result: %f\n", fvec[i],result[i]);
	}
}
