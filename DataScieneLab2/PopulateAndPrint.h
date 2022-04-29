#ifndef POPULATE_AND_PRINT_H
#define POPULATE_AND_PRINT_H
#include <iostream>
#include <cmath>
#include <time.h>
#include <chrono>
#include <omp.h>
#include <pthread.h>

using namespace std;
class PopulateAndPrint
{

public:
    PopulateAndPrint(){};

    static void print(int *x, int y)
    {
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < y; j++)
            {
                cout << *(x + j + y * i) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    static void populate(int *x, int y)
    {
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < y; j++)
            {
                *(x + j + y * i) = rand() % y;
            }
        }
    }
};
#endif