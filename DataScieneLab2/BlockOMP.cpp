#include "BlockOMP.h"

using namespace std;

int main()
{
    auto N = 0, times = 10, size = 32;
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
            auto timeBegin = std::chrono::high_resolution_clock::now();
            BlockOMP::ThreadOMP(x, N, size);
            auto timeEnd = std::chrono::high_resolution_clock::now();
            auto timeTaken = chrono::duration<double, micro>(timeEnd - timeBegin).count();
            total += timeTaken;
        }
        cout << "N = " << N << " -> Average Time: " << (total / times) << " microseconds " << endl;
        delete[] x;
    }
    return 0;
}
