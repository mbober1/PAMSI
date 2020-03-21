#pragma once
#include "utils.cpp"

template <typename T>
int quicksort_divider(T* A, int len, bool order)
{
    int pivotIdx = len / 2;
    int i = 1, j = len - 1;
    swap(A, 0, pivotIdx);

    while (i <= j) {
      while ((order ? A[i] > A[0] : A[i] < A[0]) && i < len) i++;
      while ((order ? A[j] < A[0] : A[j] > A[0])) j--;

      if (i <= j) swap(A, i++, j--);
    }

    swap(A, 0, j);
    return j;
}

template <typename T>
void quicksort(T* A, int len, bool order)
{
    if (len > 1) {
        int j = quicksort_divider(A, len, order);
        quicksort(A, j, order);
        quicksort(A + (j + 1), len - (j + 1), order);
    }
}