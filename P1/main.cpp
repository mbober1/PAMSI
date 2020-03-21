#include <iostream>
#include <math.h>
#include <random>
#include "to_excel.cpp"
#include <unistd.h>
#include "quick_sort.cpp"
#include "timer.cpp"
#include "sort_scal.cpp"
#include "introspective_sort.cpp"

#define ASCENDING 0
#define DESCENDING 1


double test(int len, int sort_type, float percentage, bool order){
    double time = 0;
    std::cout << "[";
    for(int j=0; j<100; j++){
        int* A;
        A = pick_array(A, len);
        switch(sort_type) {
            case 0: sort_scal<int>(A, len, 0, floor(len*percentage), order); break;
            case 1: quicksort<int>(A, floor(len*percentage), order); break;
            case 2: introspective_sort<int>(A, floor(len*percentage), 2*log2(len), order); break;
        }
        Timer t;
        switch(sort_type) {
            case 0: sort_scal<int>(A, len, 0, len-1, order); break;
            case 1: quicksort<int>(A, len, order); break;
            case 2: introspective_sort<int>(A, len, 2*log2(len), order); break;
        }
        time += t.elapsed();

        if(!check(A, len, order)) std::cout << "x";
        else if (j%2) std::cout << "|";
        
        std::cout.flush();
        delete[] A;
    }
    std::cout << "]" << std::endl;
    return time;
}


int main() {
    int test_table[5] = {10000, 50000, 100000, 500000, 1000000};
    ToFile file("results.txt");
    file.write("rozmiar czas posortowanie");


    std::cout << "Sortowanie przez scalanie" << std::endl;
    file.write("Scalsort");
    for(int i=0; i<5; i++){
        float percentage_array[] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 0, percentage_array[j], ASCENDING);
            std::cout << "Rozmiar: " << test_table[i] << " czas: " ;
            std::cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << std::endl; 
            std::string res_str= std::to_string(test_table[i]) + " " + std::to_string((int)(results)) + " " + std::to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }
    std::cout << "Sortowanie w odwrotnej kolejności" << std::endl;
    for(int i=0; i<5; i++){
        float percentage_array[] = {0};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 0, percentage_array[j], DESCENDING);
            std::cout << "Rozmiar: " << test_table[i] << " czas: " ;
            std::cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << std::endl; 
            std::string res_str= std::to_string(test_table[i]) + " " + std::to_string((int)(results)) + " " + std::to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }

    


    std::cout << "Sortowanie szybkie" << std::endl;
    file.write("QuickSort");
    for(int i=0; i<5; i++){
        float percentage_array[] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 1, percentage_array[j], ASCENDING);
            std::cout << "Rozmiar: " << test_table[i] << " czas: " ;
            std::cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << std::endl; 
            std::string res_str= std::to_string(test_table[i]) + " " + std::to_string((int)(results)) + " " + std::to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }
    std::cout << "Sortowanie w odwrotnej kolejności" << std::endl;
    for(int i=0; i<5; i++){
        float percentage_array[] = {0};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 1, percentage_array[j], DESCENDING);
            std::cout << "Rozmiar: " << test_table[i] << " czas: " ;
            std::cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << std::endl; 
            std::string res_str= std::to_string(test_table[i]) + " " + std::to_string((int)(results)) + " " + std::to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }

    std::cout << "Sortowanie introspektywne" << std::endl;
    file.write("Introspective");
    for(int i=0; i<5; i++){
        float percentage_array[] = {0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 2, percentage_array[j], ASCENDING);
            std::cout << "Rozmiar: " << test_table[i] << " czas: " ;
            std::cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << std::endl; 
            std::string res_str= std::to_string(test_table[i]) + " " + std::to_string((int)(results)) + " " + std::to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }
    std::cout << "Sortowanie w odwrotnej kolejności" << std::endl;
    for(int i=0; i<5; i++){
        float percentage_array[] = {0};
        for(int j = 0; j<(sizeof(percentage_array)/sizeof(int)); j++){
            double results = test(test_table[i], 2, percentage_array[j], DESCENDING);
            std::cout << "Rozmiar: " << test_table[i] << " czas: " ;
            std::cout << results << "ms  Procent posortowania: " << percentage_array[j]*100 << std::endl; 
            std::string res_str= std::to_string(test_table[i]) + " " + std::to_string((int)(results)) + " " + std::to_string((int)(100*percentage_array[j]));
            file.write(res_str);
        }
    }
    return 0;
}