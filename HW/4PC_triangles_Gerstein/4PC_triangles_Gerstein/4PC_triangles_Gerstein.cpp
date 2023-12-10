// 4PC_triangles_Gerstein.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <search.h>


struct Triangle
{
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double s;
};

void print_triangle(Triangle t)
{
    printf("(%lf, %lf), (%lf, %lf), (%lf, %lf), s=%lf\n", t.x1, t.y1, t.x2, t.y2, t.x3, t.y3, t.s);
}

double square(Triangle t)
{
    double d12 = sqrt((t.x1 - t.x2) * (t.x1 - t.x2) + (t.y1 - t.y2) * (t.y1 - t.y2));
    double d23 = sqrt((t.x3 - t.x2) * (t.x3 - t.x2) + (t.y3 - t.y2) * (t.y3 - t.y2));
    double d31 = sqrt((t.x1 - t.x3) * (t.x1 - t.x3) + (t.y1 - t.y3) * (t.y1 - t.y3));
    return sqrt((d12 + d23 + d31) * (-d12 + d23 + d31) * (d12 - d23 + d31) * (d12 + d23 - d31)) / 4.;
}

bool contains_zero(Triangle t)
{
    Triangle t12, t23, t31;
    t12 = { t.x1,t.y1,t.x2,t.y2,0.,0. };
    t23 = { t.x3,t.y3,t.x2,t.y2,0.,0. };
    t31 = { t.x1,t.y1,t.x3,t.y3,0.,0. };
    //printf("%lf, %lf, %lf, %lf\n", square(t), square(t12), square(t23), square(t31));
    return fabs(square(t) -( square(t12) + square(t23) + square(t31)))<1e-15;
}

int comparator(const void* arg1, const void* arg2)
{
    Triangle* A1 = (Triangle*)arg1;
    Triangle* A2 = (Triangle*)arg2;

    if (A1->s - A2->s > 0) return 1;
    else return -1;
}

int main()
{
    int len_file = 1000;
    Triangle* my_ts = new Triangle[len_file];
    int num_containing_zero = 0;


    FILE* file;
    freopen("triangles.txt", "r", stdin);
    for (int i = 0; i < len_file; i++)
    {
        double x1, y1, x2, y2, x3, y3;
        scanf("%lf, %lf, %lf, %lf, %lf, %lf", &x1, &y1, &x2, &y2, &x3, &y3);
        my_ts[i] = { x1, y1, x2, y2, x3, y3 };
        my_ts[i].s = square(my_ts[i]);

        if (contains_zero(my_ts[i])) num_containing_zero++;
    }
    fclose(stdin);
    
    qsort(my_ts, len_file, sizeof(Triangle), comparator);
    printf("smallest triangle:\n");
    print_triangle(my_ts[0]);
    printf("largest triangle:\n");
    print_triangle(my_ts[999]);
    printf("Number of triangles containing zero: %d\n", num_containing_zero);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
