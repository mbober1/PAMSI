#pragma once 

template <typename T>
void swap(T A[], int a, int b) {
    T bufor = A[a];
    A[a] = A[b];
    A[b] = bufor;
}

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

        H pop(bool order=0) {
            int last = this->heap_size-1;
            swap(this->heap, last, 0);
            this->heap_size--;
            this->heap_restore(0, order);
            return this->heap[last];
        }
        
        virtual H search(int id) = 0;
        virtual bool compare(int i, int j) = 0; 

        void heap_restore(int i, bool order){
            int l = this->left_child(i);
            int r = this->right_child(i);
            int max, temp;

            if(order) {
                if(l < this->heap_size && compare(l,i)){
                    max = l;
                } else {
                    max = i;
                }
                if(r < this->heap_size && compare(r,max)) max = r;

            } else {
                if(l < this->heap_size && compare(i,l)){
                    max = l;
                } else {
                    max = i;
                }
                if(r < this->heap_size && compare(max,r)) max = r;
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
