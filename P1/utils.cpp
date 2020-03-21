#pragma once

std::mt19937 generator{std::random_device{}()};

template <typename T>
void swap(T A[], int a, int b) {
    T bufor = A[a];
    A[a] = A[b];
    A[b] = bufor;
}


template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(generator);
}



template <typename T>
bool check(T A[], int len, bool order) {
    for(int i=0; i<len-1; i++){

        if(order) {
            if(A[i+1]>A[i]) {
                return false; //błąd sortowania
            }
        } else {
            if(A[i+1]<A[i]) {
                return false; //błąd sortowania
            }
        }
    }
    return true;
}


int* pick_array(int* A, int len, int min=0, int max=1000) {
    A = new int[len];
    for (int i = 0; i<len; i++){
        A[i] = random<int>(min,max);
    }
    return A;
}

