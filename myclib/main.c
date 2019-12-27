#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "memory-management/allocator.h"
#include "memory-management/vector.h"


int main() {
    struct vector vec;
    vector_init(&vec, sizeof(int), 5);
    int i = 3;
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    vector_pushback(&vec, &i);
    return 0;
}