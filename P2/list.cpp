#include <iostream>


template <typename T>
class List_element {
    public:
        T data;
        List_element* next;

        List_element(T data) {
            this->data = data;
        }

};


template <typename T>
class List {
    public:
        List_element<T>* elements;
        int size;

        List() {
            this->size = 0;
            elements = nullptr;

        }

        List_element<T>* add_element(T data) {
            List_element<T>* element = new List_element<T>(data);
            List_element<T>* tmp = elements;

            if(!tmp) {
                tmp = element;
                elements = tmp;
            } else {

                while(tmp->next) {
                    tmp = tmp->next;
                }

            tmp->next = element;
            }


            this->size++;
            return element;
        }

        void show_me_your_list() {
            List_element<T>* tmp = elements;
            while(tmp) {
                std::cout << tmp->data << " ";
                tmp = tmp->next;
            }
        }
};
