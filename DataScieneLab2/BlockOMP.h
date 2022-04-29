#ifndef BLOCKOMP_H
#define BLOCKOMP_H
#include "PopulateAndPrint.h"

using namespace std;

class BlockOMP
{
public:
    static void swop(int *x, int i, int j, int N, int size)
    {
        for (int k = 0; k < size; k++)
        {
            for (int l = 0; l < size; l++)
            {
                int hold = *(x + (k + i) * N + l + j);
                *(x + (k + i) * N + l + j) = *(x + (j + k) * N + i + l);
                *(x + (j + k) * N + i + l) = hold;
            }
        }
    }

    static void transpose(int *x, int N, int size)
    {
#pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < N; i += size)
        {
            for (int j = 0; j < N; j += size)
            {
                for (int k = 0; k < size; k++)
                {
                    for (int l = k; l < size; l++)
                    {
                        if (l > k)
                        {
                            int hold = *(x + (k + i) * N + l + j);
                            *(x + (k + i) * N + l + j) = *(x + (l + i) * N + k + j);
                            *(x + (l + i) * N + k + j) = hold;
                        }
                    }
                }
            }
        }
    }

    static void blockTrans(int *x, int N, int size)
    {
#pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < N; i += size)
        {
            for (int j = i; j < N; j += size)
            {
                if (j > i)
                {
                    swop(x, i, j, N, size);
                }
            }
        }
    }

    static void ThreadOMP(int *x, int N, int size)
    {
        transpose(x, N, size);
        blockTrans(x, N, size);
    }
};
#endif