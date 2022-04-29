#include "PopulateAndPrint.h"

using namespace std;
int main()
{
    int N, times = 10;
    for (int count = 0; count < 4; count++)
    {
        if (count == 0)
        {
            N = 128;
        }
        else if (count == 1)
        {
            N = 1024;
        }
        else if (count == 2)
        {
            N = 2048;
        }
        else if (count == 3)
        {
            N = 4096;
        }
        auto total = 0;
        auto *x = new int[N * N];
        for (int i = 0; i < times; i++)
        {
            PopulateAndPrint::populate(x, N);
            auto timeBegin = chrono::high_resolution_clock::now();
#pragma omp parallel for schedule(dynamic)
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    int hold = *(x + i * N + j);
                    *(x + i * N + j) = *(x + j * N + i);
                    *(x + j * N + i) = hold;
                }
            }
            auto timeEnd = chrono::high_resolution_clock::now();
            auto timeTaken = chrono::duration<double, micro>(timeEnd - timeBegin).count();
            total += timeTaken;
        }
        cout << "N = " << N << " -> Average Time: " << (total / times) << " microseconds " << endl;
        delete[] x;
    }
}