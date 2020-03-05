#pragma once
#include "quick_sort.cpp"
#include "heap_sort.cpp"

template <typename T>
void introspective_sort(T A[], int left, int right, int depth) {
    Heap heap(A, right-left+1);
    if (left < right) {
        if (depth > 0) {
            int m = left; //wypieramy pivot
            for(int i=left+1; i<=right; i++) { //przypisujemy liczby do lewej lub prawej części (pivot, mniejsze, większe)
                if (A[i] < A[left]) {
                    m++;
                    swap(A,i,m);
                }
            }
            swap(A,left,m); //zamiana pivota z ostatnim mniejszym
            introspective_sort(A, left, m-1, depth-1);
            introspective_sort(A, m+1, right, depth-1);
        
        } else {
            heap_sort(heap);
        }

    }
}

// template <class var>
// void Sorts::iS( var tab[], int firstIndex, int lastIndex, int maxDepth ) {
//     if ( firstIndex < lastIndex ) {
//         if ( !maxDepth ) {
//             hS( tab, firstIndex, lastIndex );
//             return;
//         }
//         int n = qs_split( tab, firstIndex, lastIndex, false );
//         iS( tab, firstIndex, n-1, maxDepth-1 );
//         iS( tab, n+1, lastIndex, maxDepth-1 );
//     }
// }