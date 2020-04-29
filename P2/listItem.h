template<typename T>
class ListItem {
public:
  T data;
  ListItem* next = nullptr;

  ListItem(const T& x) {
    this->data = x;
  }
};
