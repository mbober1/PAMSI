template<typename T>
class List {
public:
  ListItem<T>* head;
  size_t size;

  List() {
    head = nullptr;
    size = 0;
  }

  ~List() {
    ListItem<T>* tmp = this->head;

    while(this->head) {
      tmp = this->head->next;
      delete this->head;
      this->head = tmp;
    }
  }

  void append(const T& data) {
    ListItem<T>* tmp = head;
    ListItem<T>* newItem = new ListItem<T>(data);

    if (!tmp) head = newItem;
    else {
      while (tmp->next) tmp = tmp->next;
      tmp->next = newItem;
    }
    size++;
  }


  class iterator {
  public:
    iterator(ListItem<T>* curr): curr(curr) {}
    iterator operator++() { curr = curr->next; return *this; }
    bool operator!=(const iterator& other) const { return curr != other.curr; }
    const T& operator*() const { return curr->data; }

  private:
    ListItem<T>* curr;
  };

  iterator begin() const { return iterator(head); }
  iterator end() const { return iterator(nullptr); }

  friend std::ostream & operator<<(std::ostream & out, const List<T> & list)
  {
    for(T item : list) {
      if (!item) continue;
      out << ((*item).destination) << " ";
    }

    return out;
  }
};
