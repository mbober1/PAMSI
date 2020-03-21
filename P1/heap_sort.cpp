#pragma once 
#include "utils.cpp"


template <typename H>
class Heap {
    public:
        int heap_size;
        int size;
        H* heap;

        Heap(H* A, int size) {
            this->heap = A;
            this->size = size;
        }

        void heap_restore(int i, bool order){
            int l = this->left_child(i);
            int r = this->right_child(i);
            int max, temp;

            if(order) {
                if(l < this->heap_size && this->heap[l] < this->heap[i]){
                    max = l;
                } else {
                    max = i;
                }
                if(r < this->heap_size && this->heap[r] < this->heap[max]) max = r;

            } else {
                if(l < this->heap_size && this->heap[l] > this->heap[i]){
                    max = l;
                } else {
                    max = i;
                }
                if(r < this->heap_size && this->heap[r] > this->heap[max]) max = r;
            }



            if(max != i) {
                swap(this->heap, i, max);
                heap_restore(max, order);
            }
        }

        int left_child(int i) { //zwraca index lewego bombelka
            return 2*i+1;
        }

        int right_child(int i) { //zwraca index prawego bombelka
            return 2*i+2;
        }

        void heap_build(bool order) {
            this->heap_size = this->size;
            for(int i=this->size/2; i>=0; i--){
                heap_restore(i, order);
            }
        }
};

template <typename T>
void heap_sort(T A[], int len, bool order) {
    Heap<T> heap(A, len);
    heap.heap_build(order);    

    for(int i = heap.size-1; i > 0; i--) {
        swap(heap.heap, i, 0);
        heap.heap_size--;
        heap.heap_restore(0, order);
    }
}