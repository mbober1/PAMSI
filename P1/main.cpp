// nie użuwaj STL'a nigdy


#include <iostream>
#include <math.h>
#include <random>
#include "timer.cpp"
#include "sort_scal.cpp"

using namespace std;
mt19937 generator{random_device{}()};

template<typename T>
T random(T min, T max) {
    return uniform_int_distribution<T>{min, max}(generator);
}

#define ASCENDING 0
#define DESCENDING 1


int* pick_array(int* A, int len, int min=0, int max=1000) {
    A = new int[len];
    for (int i = 0; i<len; i++){
        A[i] = random<int>(min,max);
    }
    return A;
}

double test_algorithm(int len, float percentage=0, int order=ASCENDING){
    double time = 0;
    for(int j=0; j<100; j++){
        int* A;
        A = pick_array(A, len);
        sort_scal<int>(A, len, 0, floor(len*percentage));

        Timer t;
        sort_scal<int>(A, len, 0, len-1);
        time += t.elapsed();
    }
    return time;
}



int main() {
    int test_table[5] = {10000, 50000, 100000, 1, 0};


    for(int i=0; i<5; i++){
        cout << "Rozmiar: " << test_table[i] << " czas: " ;
        cout << test_algorithm(test_table[i]) << "ms" << endl; 
    }


    for(int i=0; i<5; i++){
        float percentage_array[] = {0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
        for(int j = 0; j<6; j++){
            cout << "Rozmiar: " << test_table[i] << " czas: ";
            cout << test_algorithm(test_table[i]) << "ms  Procent posortowania: " << percentage_array[j]*100 << endl;
        }
    }
    
    return 0;
}

