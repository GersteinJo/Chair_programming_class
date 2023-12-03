﻿// 1PC_hypergeometric_Gerstein.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <math.h>

long double f_hyper_gem(long double a, long double b, long double c, long double z, long double error)
{
    long double hyper_gem = 1., epsilon = 1., coef = 1.;
    int n = 1;
    do
    {
        coef *= (a + n - 1) * (b + n - 1) / (c + n - 1) / n * z;
        epsilon = coef;
        hyper_gem += epsilon;
        n++;
    } while ((fabs(epsilon) > error));
    return hyper_gem;
}

long double F_pt2(long double a, long double b, long double c, long double z, long double error)
{
    if (fabs(z) <= 0.5) 
        return f_hyper_gem(a, b, c, z, error);

    else if ((z < -0.5))
        return 1 / powl(1 - z, a) * f_hyper_gem(a, c - b, c, z / (z - 1), error);

    else if ((z <= 1.0) && (z > 0.5) && (c - a - b != 0.0))
        return (exp(lgammal(c) + lgammal(c - a - b) - lgammal(c - a) - lgammal(c - b)) *
        f_hyper_gem(a, b, a + b - c + 1, 1 - z, error) +
        powl(1 - z, c - a - b) * exp(lgammal(c) + lgammal(a + b - c) - lgammal(a) - lgammal(b)) *
        f_hyper_gem(c - a, c - b, c - a - b + 1, 1 - z, error));

    return f_hyper_gem(a, b, c, z, error);
}

int main()
{
    printf("RART 1\n");
    long double hyper_gem_log, hyper_gem_asin, my_log, my_asin, error = 1e-10;
    printf("z \t\t F(1, 1, 2, z) \t 1/z ln(1-z) \t F(1/2, 1/2, 3/2, z^2) \t 1/z asin(z) \n");
    for (long double z = -0.95; z < 0.; z = z + 0.1)
    {
        my_log = -logl(1 - z) / z;
        hyper_gem_log = f_hyper_gem(1, 1, 2, z, error);
        printf("%Lf \t %Lf \t %Lf \t -- \t\t\t -- \n", z, hyper_gem_log, my_log );
    }
    for (long double z = 0.05; z < 1.; z = z + 0.1)
    {
        my_log = -logl(1 - z) / z;
        my_asin = asinl(z) / z;
        hyper_gem_log = f_hyper_gem(1, 1, 2, z, error);
        hyper_gem_asin = f_hyper_gem(0.5L, 0.5L, 1.5L, z*z, error);
        printf("%Lf \t %Lf \t %Lf \t %Lf \t\t %Lf \n", z, hyper_gem_log, my_log, hyper_gem_asin, my_asin);
    }
    printf("________________________________________________________________________________________________________________________\n");
    printf("________________________________________________________________________________________________________________________\n");

    long double hyper_gem_atan, my_atan, hyper_gem_beast, my_beast;
    printf("RART 2\n");
    printf("z \t\t F(1/2, 1, 3/2, -z^2) \t 1/z atan(z) \t F(-1/4, 1/4, 1/2, -z^2) \t BigBadFunc \n");
    for (long double z = 0; z < 0.5; z = z + 0.05)
    {
        hyper_gem_atan = F_pt2(0.5, 1., 1.5, -z* z, error);
        my_atan = z!=0.?atanl(z)/z:1;
        hyper_gem_beast = F_pt2(-0.25, 0.25, 0.5, -z* z, error);
        my_beast = 0.5 * (powl(powl(1 + z* z, 0.5) + z, 0.5) + powl(powl(1 + z* z, 0.5) - z, 0.5));
        printf("%Lf \t %Lf \t\t %Lf \t %Lf \t\t\t %Lf \n", z, hyper_gem_atan, my_atan, hyper_gem_beast, my_beast);
    }
    printf("________________________________________________________________________________________________________________________\n");
    for (long double z = 0.5; z < 1.5; z = z + 0.1)
    {
        hyper_gem_atan = F_pt2(0.5, 1., 1.5, -z * z, error);
        my_atan = atanl(z) / z;
        hyper_gem_beast = F_pt2(-0.25, 0.25, 0.5, -z * z, error);
        my_beast = 0.5 * (powl(powl(1 + z * z, 0.5) + z, 0.5) + powl(powl(1 + z * z, 0.5) - z, 0.5));
        printf("%Lf \t %Lf \t\t %Lf \t %Lf \t\t\t %Lf \n", z, hyper_gem_atan, my_atan, hyper_gem_beast, my_beast);
    }
    printf("________________________________________________________________________________________________________________________\n");
    for (long double z = 1.5; z <= 10; z = z + 0.5)
    {
        hyper_gem_atan = F_pt2(0.5, 1., 1.5, -z* z, error);
        my_atan = atanl(z) / z;
        hyper_gem_beast = F_pt2(-0.25, 0.25, 0.5, -z* z, error);
        my_beast = 0.5 * (powl(powl(1 + z* z, 0.5) + z, 0.5) + powl(powl(1 + z* z, 0.5) - z, 0.5));
        printf("%Lf \t %Lf \t\t %Lf \t %Lf \t\t\t %Lf \n", z, hyper_gem_atan, my_atan, hyper_gem_beast, my_beast);
    }
}


