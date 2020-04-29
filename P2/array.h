template<typename T>
class Array {
public:
  T* head;
  size_t size = 0;

  void append(const T& data) {
    T* newArray = new T[size+1];
    for (int i = 0; i < size; ++i) newArray[i] = head[i];
    newArray[size] = data;
    delete[] head;
    head = newArray;
    size++;
  }

  class iterator {
  public:
    iterator(T* ptr): ptr(ptr) {}
    iterator operator++() { ++ptr; return *this; }
    bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    const T& operator*() const { return *ptr; }

  private:
    T* ptr;
  };

  iterator begin() const { return iterator(head); }
  iterator end() const { return iterator(head + size); }
};