#include "testGlobalThreadPoolInit.h"
#include <IlmThreadPool.h>
#include <iostream>
#include <vector>
#include <cassert>

#if defined(_OPENMP)
#include <omp.h>
#endif


using namespace std;


namespace
{
inline int globalThreadCount () {
    return IlmThread::ThreadPool::globalThreadPool().numThreads();
}
} // namespace


void
testGlobalThreadPoolInit ()
{
    cout << "thread-safe creation of the global thread pool" << endl;

#if defined(_OPENMP)
    const int numThreads = omp_get_max_threads();
    const int N = numThreads * 8;
    cout << "OpenMP default number of threads = " << numThreads << endl;
#else
    const int N = 8;
    cout << "Warning: the test is not meaningful without OpenMP support."
         << endl << flush;
#endif

    // Warm up
    cout << "Warm up..." << endl;
    std::vector<int> a(N);
    #pragma omp parallel for schedule(static,1) num_threads(N)
    for (int i = 0; i < N; ++i) {
        a[i] = i*i;
    }

    cout << "Torture testing with " << N << " threads..." << endl;
    #pragma omp parallel for schedule(static,1) num_threads(N)
    for (int i = 0; i < N; ++i) {
        a[i] = globalThreadCount();
    }

    for (int i = 1; i < N; ++i) {
        assert (a[0] == a[i]);
    }
    cout << "global thread count = " << a[0] << endl;

    cout << "ok\n\n" << flush;
}
