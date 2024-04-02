#pragma once

#ifndef NDEBUG
#include <iostream>
#define DEBUG(x)        \
    do {                \
        std::cout << x; \
    } while (0)
#else
#define DEBUG(x)
#endif
