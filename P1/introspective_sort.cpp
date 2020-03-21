#pragma once
#include "quick_sort.cpp"
#include "heap_sort.cpp"

template <typename T>
void introspective_sort(T A[], int len, int depth, bool order) {
    if (len > 1) {
        if (depth > 0) {
            int j = quicksort_divider(A, len, order);
            introspective_sort(A, j, depth-1, order);
            introspective_sort(A + (j + 1), len - (j + 1), depth-1, order);
        } else {
            heap_sort(A, len, order);
        }
    }
}