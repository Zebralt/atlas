#ifndef container_hpp__
#define container_hpp__

#include <vector>

template <typename T>
class Container {
public:
    std::vector<T> _items;
    virtual void add(T t) { _items.push_back(t); }
    virtual std::vector<T>& items() { return _items; }
    virtual T get(const int& i) {if (i >= 0 && i < _items.size()) return _items[i];}
};

template <typename T>
class List : public Container<T> {
public:
    int index_of(T a);
    
};

template <typename T>
class CycleList : public List<T> {
    int cursor = 0;
public:
    virtual void next();
    virtual void previous();
    virtual void cycle(int i);
};

#endif // container_hpp__