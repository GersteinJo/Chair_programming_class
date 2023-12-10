#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

double* uniform_dist_array(int n, double arr_min = 0., double arr_max = 1.)
	/* generates an array with uniform distribution on segment [0,1]
	IN: n -- length of the array
		arr_min -- smaller border of the segment
		arr_max -- greater borged
	OUT: reference to the new array
	*/
{
	srand(time(NULL));
	double* new_array = new double[n];
	for (int i = 0; i < n; i++)
	{
		new_array[i] = (double)rand() / RAND_MAX * (arr_max-arr_min) + arr_min;
	}	
	return new_array;

}

double* normal_dist_array(int n, double mean = 0., double std=1.)
/* generates an array with standard distribution basic params: mean  = 0, std = 1
* uses Box-Muller algorithm
IN: n -- length of the array
	mean -- mean value
	std -- standard deviation
OUT: reference to the new array
*/
{

	//generate array uniformly distributed on segment [0,1]
	int len_u = (n % 2 == 0) ? n : (n + 1);
	double* u = uniform_dist_array(len_u);
	double pi = 3.1415926536;
	double* new_array = new double[n];
	for (int i = 0; i < len_u; i=i+2)
	{
		double R = sqrt(-2 * log(u[i]));
		double x = cos(2 * pi * u[i + 1]);
		double y = sin(2 * pi * u[i + 1]);
		u[i] = R * x;
		u[i + 1] = R * y;
	}

	for (int i = 0; i < n; i++) new_array[i] = u[i];

	return new_array;

}

double mean(double* array, int len)
{
	double mean = 0.0;
	for (int i = 0; i < len; i++)
	{
		mean = mean + array[i];
	}
	mean /= len;
	return mean;
}

double* moments(double* array, int len, int n)
/*
* calculates moments up to nth and stores them in an array
* IN: array -- an array of numbers on which we'll be calculating the moments
*	  len   -- number of elements in array
*	  n     -- number of momnets we want to aquire
* OUT: an array containing moments up to nth
*/
{
	double* moment = new double[n+1];
	double _mean_ = mean(array, len);
	for (int num = 0; num < n + 1; num++) moment[num] = 0.;

	for (int num = 0; num < n + 1; num++)
		for (int i = 0; i < len; i++) moment[num] = moment[num] + pow((array[i] - _mean_), num) / len;
	
	return moment;
}




int main()
{

	int len_of_arr;
	scanf("%d", &len_of_arr);
	double* my_new_array = uniform_dist_array(len_of_arr);
	printf("Uniformly distributed array:\n");
	//for (int i = 0; i < len_of_arr; i++)
	//	printf("%lf , ", my_new_array[i]);

	double* uniform_moments = moments(my_new_array, len_of_arr, 4);
	printf("\n________________\n MEAN: %lf \n STD: %lf \n SKEWNESS: %lf \n KURTOSIS: %lf\n\n",
		mean(my_new_array, len_of_arr), sqrt(uniform_moments[2]), uniform_moments[3] / pow(uniform_moments[2], 1.5),
		uniform_moments[4] / pow(uniform_moments[2], 2.) - 3.);


	double* my_normal_array = normal_dist_array(len_of_arr);
	printf("normally distributed array:\n");
	//for (int i = 0; i < len_of_arr; i++)
	//	printf("%lf , ", my_normal_array[i]);

	double* normal_moments = moments(my_normal_array, len_of_arr, 4);
	printf("\n________________\n MEAN: %lf \n STD: %lf \n SKEWNESS: %lf \n KURTOSIS: %lf\n\n",
		mean(my_normal_array, len_of_arr), sqrt(normal_moments[2]), normal_moments[3] / pow(normal_moments[2], 1.5),
		normal_moments[4] / pow(normal_moments[2], 2.) - 3.);



	int len_landau = 100000;
	int num_read;
	double* landau = new double[len_landau];
	
	FILE* file = fopen("Landau.txt", "r");
	if (!file) {
		printf("FILE NOT FOUND\n");
		exit(1);
	}

	for (int i = 0; i < len_landau; i++)
	{
		fscanf(file, "%lf", &landau[i]);
	}

	/*freopen("Landau.txt", "r", stdin);
	for (int i = 0; i < len_landau; i++)
	{
		scanf("%lf", &landau[i]);
	}
	fclose(stdin);*/
	double* landau_moments = moments(landau, len_landau, 4);
	printf("\n________________\n MEAN: %lf \n STD: %lf \n SKEWNESS: %lf \n KURTOSIS: %lf\n\n",
		mean(landau, len_landau), sqrt(landau_moments[2]), landau_moments[3] / pow(landau_moments[2], 1.5),
		landau_moments[4] / pow(landau_moments[2], 2.) - 3.);

}
