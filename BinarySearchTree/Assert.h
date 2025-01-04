#pragma once
#include <iostream>

#define ASSERTMSG(exp, msg)                                  \
    if (!(exp))                                              \
        std::cout << "***ASSERT FAILED***: " << msg << '\n'; \

#define ASSERT(exp) ASSERTMSG(exp, #exp)
