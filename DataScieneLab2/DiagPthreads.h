#ifndef DIAGPTHREADS_H
#define DIAGPTHREADS_H
#include "PopulateAndPrint.h"

using namespace std;

class DiagPthreads
{
public:
    struct vars
    {
        int currThread;
        int threadNum;
        int *array;
        int N;
    };

    static void *diagPThread(void *x)
    {
        vars *val = (vars *)x;
        int N = val->N;
        for (int i = val->currThread; i < val->N; i += val->threadNum)
        {
            for (int j = i; j < val->N; j++)
            {
                int hold = *(val->array + j + i * N);
                *(val->array + i * N + j) = *(val->array + j * N + i);
                *(val->array + j * N + i) = hold;
            }
        }
        return NULL;
    }

    static void newThread(int *x, int N, int threadNum)
    {
        vars *val = new vars[threadNum];
        pthread_t threads[threadNum];
        for (int i = 0; i < threadNum; i++)
        {
            (val + i)->threadNum = threadNum;
            (val + i)->array = x;
            (val + i)->currThread = i;
            (val + i)->N = N;
            pthread_create(&threads[i], NULL, diagPThread, (val + i));
        }
        for (int i = 0; i < threadNum; i++)
        {
            pthread_join(threads[i], NULL);
        }
    }
};
#endif