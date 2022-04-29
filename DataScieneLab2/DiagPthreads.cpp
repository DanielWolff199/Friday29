#include "DiagPthreads.h"

using namespace std;

int main()
{
    auto N = 0, times = 10, threadNum = 4;
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
            DiagPthreads::newThread(x, N, threadNum);
            auto timeEnd = chrono::high_resolution_clock::now();
            auto timeTaken = chrono::duration<double, micro>(timeEnd - timeBegin).count();
            total += timeTaken;
        }
        cout << "N = " << N << " -> Average Time: " << (total / times) << " microseconds " << endl;
        delete[] x;
    }
}