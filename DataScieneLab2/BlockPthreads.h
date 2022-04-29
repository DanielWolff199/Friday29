#ifndef BLOCKPTHREADS_H
#define BLOCKPTHREADS_H
#include "PopulateAndPrint.h"

using namespace std;

class BlockPthreads
{
public:
    struct vars
    {
        int currThread;
        int threadNum;
        int *array;
        int N;
        int block;
    };

    static void *blockTrans(void *p)
    {
        vars *val = (vars *)p;
        int N = val->N;
        for (int i = val->block * val->currThread; i < N; i += val->threadNum * val->block)
        {
            for (int j = i; j < N; j += val->block)
            {
                if (j > i)
                {
                    for (int k = 0; k < val->block; k++)
                    {
                        for (int l = 0; l < val->block; l++)
                        {
                            int hold = *(val->array + (k + i) * N + l + j);
                            *(val->array + (k + i) * N + l + j) = *(val->array + (j + k) * N + i + l);
                            *(val->array + (j + k) * N + i + l) = hold;
                        }
                    }
                }
            }
        }
        return NULL;
    };

    static void *transpose(void *p)
    {
        vars *val = (vars *)p;
        int N = val->N;
        for (int i = val->currThread * val->block; i < N; i += val->threadNum * val->block)
        {
            for (int j = 0; j < N; j += val->block)
            {
                for (int k = 0; k < val->block; k++)
                {
                    for (int l = k; l < val->block; l++)
                    {
                        if (l > k)
                        {
                            int hold = *(val->array + (k + i) * N + l + j);
                            *(val->array + (k + i) * N + l + j) = *(val->array + (l + i) * N + k + j);
                            *(val->array + (l + i) * N + k + j) = hold;
                        }
                    }
                }
            }
        }
        return NULL;
    };

    static void newThread(int *a, int N, int threadNum, int block)
    {
        vars *val = new vars[threadNum];
        pthread_t threads[threadNum];

        for (int i = 0; i < threadNum; i++)
        {
            (val + i)->threadNum = threadNum;
            (val + i)->array = a;
            (val + i)->currThread = i;
            (val + i)->block = block;
            (val + i)->N = N;
        }
        for (int i = 0; i < threadNum; i++)
        {
            pthread_create(&threads[i], NULL, transpose, (val + i));
        }
        for (int i = 0; i < threadNum; i++)
        {
            pthread_join(threads[i], NULL);
        }
        for (int i = 0; i < threadNum; i++)
        {
            (val + i)->currThread = i;
            pthread_create(&threads[i], NULL, blockTrans, (val + i));
        }
        for (int i = 0; i < threadNum; i++)
        {
            pthread_join(threads[i], NULL);
        }
    }
};
#endif