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

double test_algorithm_quick(int len, float percentage=0, int order=ASCENDING){
    
    double results = 0;
    for(int j=0; j<100; j++){
        int* A;
        A = pick_array(A, len);
        quicksort<int>(A, 0, floor(len*percentage));

        Timer t;
        quicksort<int>(A, 0, len-1);
        results += t.elapsed();
    }
    return results;
}


int main() {
    // int* A;
    // int len = 10;
    // // A = pick_array(A, len);
    // int A[10] = {3,1,5,8,10,12,4,7,2};
    // // quicksort<int>(A, 0, len-1);

    // // for(int j = 0; j<len; j++){
    // //     cout << A[j] << " ";
    // // }




    int test_table[5] = {10000, 50000, 100000, 500000, 1000000};
    ToFile file("excel.txt");

    // Heap <int>krecik(A, len);
    // heap_sort(krecik);

    // for(int j = 0; j<len; j++){
    //     cout << A[j] << " ";
    // }
    

    // cout << "Sortowanie przez scalanie" << endl;
    // file.write("Sortowanie przez scalanie");
    // for(int i=0; i<5; i++){
    //     double results = test_algorithm(test_table[i]);
    //     cout << "Rozmiar: " << test_table[i] << " czas: " ;
    //     cout << results << "ms" << endl; 
    //     file.write("rozmiar czas posortowanie");
    //     string res_str= to_string(test_table[i]) + " " + to_string(results) + " " + '0';
    //     file.write(res_str);
    // }


    // for(int i=0; i<5; i++){
    //     float percentage_array[] = {0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
    //     for(int j = 0; j<6; j++){
    //         double results = test_algorithm(test_table[i]);
    //         cout << "Rozmiar: " << test_table[i] << " czas: " ;
    //         cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << endl; 
    //         string res_str= to_string(test_table[i]) + " " + to_string(results) + " " + to_string(percentage_array[j]);
    //         file.write(res_str);
    //     }
    // }

    cout << "Sortowanie szybkie" << endl;
    file.write("QuickSort");
    for(int i=0; i<5; i++){
        double results = test_algorithm_quick(test_table[i]);
        cout << "Rozmiar: " << test_table[i] << " czas: " ;
        cout << results << "ms" << endl; 
        file.write("rozmiar czas posortowanie");
        string res_str= to_string(test_table[i]) + " " + to_string(results) + " " + '0';
        file.write(res_str);
    }

    // for(int i=0; i<5; i++){
    //     float percentage_array[] = {0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
    //     for(int j = 0; j<6; j++){
    //         double results = test_algorithm_quick(test_table[i]);
    //         cout << "Rozmiar: " << test_table[i] << " czas: " ;
    //         cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << endl; 
    //         string res_str= to_string(test_table[i]) + " " + to_string(results) + " " + to_string(percentage_array[j]);
    //         file.write(res_str);
    //     }
    // }    

    return 0;
}

