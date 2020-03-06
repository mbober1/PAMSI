// nie użuwaj STL'a nigdy

#include <iostream>
#include <math.h>
#include <random>
#include "timer.cpp"
#include "sort_scal.cpp"
#include "quick_sort.cpp"
#include "to_excel.cpp"
#include <unistd.h>
#include "heap_sort.cpp"
#include "introspective_sort.cpp"

using namespace std;
mt19937 generator{random_device{}()};

template<typename T>
T random(T min, T max) {
    return uniform_int_distribution<T>{min, max}(generator);
}

#define ASCENDING 0
#define DESCENDING 1



template <typename T>
bool check(T A[], int len) {
    for(int i=0; i<len-1; i++){
        if(A[i+1]<A[i]) {
            return false; //błąd sortowania
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


double test(int len, int sort_type, float percentage){
    double time = 0;
    cout << "[";
    for(int j=0; j<100; j++){
        int* A;
        A = pick_array(A, len);
        switch(sort_type) {
            case 0: sort_scal<int>(A, len, 0, floor(len*percentage)); break;
            case 1: quicksort<int>(A, 0, floor(len*percentage)); break;
            case 2: introspective_sort<int>(A, 0, floor(len*percentage), 2*log2(len)); break;
        }
        Timer t;
        switch(sort_type) {
            case 0: sort_scal<int>(A, len, 0, len-1); break;
            case 1: quicksort<int>(A, 0, len-1); break;
            case 2: introspective_sort<int>(A, 0, len-1, 2*log2(len)); break;
        }
        time += t.elapsed();
        
        if(!check(A, len)) cout << "x";
        else if (j%2) cout << "|";
        
        cout.flush();
        delete[] A;
    }
    cout << "]" << endl;
    return time;
}




int main() {
    int test_table[5] = {10000, 50000, 100000, 500000, 1000000};
    ToFile file("excel.txt");
    file.write("rozmiar czas posortowanie");


    cout << "Sortowanie przez scalanie" << endl;
    file.write("Scalsort");
    for(int i=0; i<5; i++){
        float percentage_array[] = {0};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 0, percentage_array[j]);
            cout << "Rozmiar: " << test_table[i] << " czas: " ;
            cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << endl; 
            string res_str= to_string(test_table[i]) + " " + to_string((int)(results)) + " " + to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }

    cout << "Sortowanie szybkie" << endl;
    file.write("QuickSort");
    for(int i=0; i<5; i++){
        float percentage_array[] = {0};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 1, percentage_array[j]);
            cout << "Rozmiar: " << test_table[i] << " czas: " ;
            cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << endl; 
            string res_str= to_string(test_table[i]) + " " + to_string((int)(results)) + " " + to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }

    cout << "Sortowanie introspektywne" << endl;
    file.write("Introspective");
    for(int i=0; i<5; i++){
        float percentage_array[] = {0};
        // float percentage_array[] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 2, percentage_array[j]);
            cout << "Rozmiar: " << test_table[i] << " czas: " ;
            cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << endl; 
            string res_str= to_string(test_table[i]) + " " + to_string((int)(results)) + " " + to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }


    return 0;
}