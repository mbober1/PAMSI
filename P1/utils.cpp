#pragma once

template <typename T>
void swap(T A[], int a, int b) {
    T bufor = A[a];
    A[a] = A[b];
    A[b] = bufor;
}