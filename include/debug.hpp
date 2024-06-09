#pragma once

#ifndef NDEBUG
#include <iostream>
#include <string>
#define S(x) std::to_string(x)
#define DEBUG(x)                                     \
    do {                                             \
        std::cout << std::string() + x << std::endl; \
    } while (0)
#else
#define DEBUG(x)
#endif
