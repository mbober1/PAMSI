// nie użuwaj STL'a nigdy


#include <iostream>
#include <math.h>
#include <random>
#include "timer.cpp"

using namespace std;
mt19937 generator{random_device{}()};

template<typename T>
T random(T min, T max) {
    return uniform_int_distribution<T>{min, max}(generator);
}

#define ASCENDING 0
#define DESCENDING 1

template <typename T>
void scal(T A[], int len, int left, int mid, int right) {

    int i = left;
    int j = mid + 1;
    int k = left;
    T B[len];

    while (i <= mid && j<= right) //przejdź przez wszystkie elementy
    {
        if (A[i] < A[j]) //porównywanie
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    while (i <= mid) //dopełnienie elementami z pierwszej połówki
    {
        B[k] = A[i];
        i++;
        k++;
    }

    while (j <= right) //dopełnienie elementami z drugiej połówki
    {
        B[k] = A[j];
        j++;
        k++;
    }

    for(i = left; i <= right; i++) //przepisanie elementów z B do A
    {
        A[i] = B[i]; 
    }
    
}

template <typename T>
void sort_scal(T A[], int len, int left, int right) {
    if (left < right)
    {
        int mid = floor((left+right)/2);    //liczenie środka
        sort_scal<T>(A, len, left, mid);       //sortujemy lewą część
        sort_scal<T>(A, len, mid+1, right);    //sortujemy prawą część
        scal<T>(A, len, left, mid, right);     //scalamy obie części
    }
    
}


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

