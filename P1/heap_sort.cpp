#pragma once 
#include "utils.cpp"

template <typename H>
class Heap {
    public:
        int heap_size;
        int size;
        H* heap;

        Heap(H* A, int len) {
            this->heap = A;
            this->size = len;
        }

        void heap_restore(int i){
            int l = this->left(i);
            int r = this->right(i);
            int max, temp;


            if(l < this->heap_size && this->heap[l] > this->heap[i]){
                max = l;
            } else {
                max = i;
            }
            if(r < this->heap_size && this->heap[r] > this->heap[max]) max = r;

            if(max != i) {
                swap(this->heap, i, max);
                heap_restore(max);
            }
        }

        int left(int i) { //zwraca index lewego bombelka
            return 2*i+1;
        }

        int right(int i) { //zwraca index prawego bombelka
            return 2*i+2;
        }

        void heap_build(int lenght) {
            this->heap_size = lenght;
            for(int i=lenght/2; i>=0; i--){
                heap_restore(i);
            }
        }
};

template <typename T>
void heap_sort(Heap<T> &heap, int left, int right) {
    heap.heap_build(heap.size);    

    for(int i = heap.size-1; i > 0; i--) {
        swap(heap.heap, i, 0);
        heap.heap_size--;
        heap.heap_restore(0);
    }
}