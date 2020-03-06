#pragma once
#include "quick_sort.cpp"
#include "heap_sort.cpp"

template <typename T>
void introspective_sort(T A[], int left, int right, int depth) {
    if (left < right) {
        if (depth > 0) {
            int m = quicksortdupa(A,left, right);
            introspective_sort(A, left, m-1, depth-1);
            introspective_sort(A, m+1, right, depth-1);
        
        } else {
            heap_sort(A, left, right);
        }

    }
}
