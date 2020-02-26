#include <stdio.h>
#include "NestedLoop.hpp"

#define DEBUG_OUTPUT

int main() {
    int32_t result = NestedLoop();
    #if defined(DEBUG_OUTPUT)
    //printf("Result=%d\n", result);
    #endif
    return result;
}

