#include "testGlobalThreadPoolInit.h"

#include <iostream>
#include <cstring>


#define TEST(x) if (argc < 2 || !strcmp (argv[1], #x)) x();


int
main (int argc, char *argv[])
{
    std::cout << "\ntesting thread library:\n\n" << std::flush;

    TEST (testGlobalThreadPoolInit);

    return 0;
}
