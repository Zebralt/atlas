#ifndef container_hpp__
#define container_hpp__

#include <vector>

template <typename T>
class Container {
public:
    virtual void add(T t) { items.push_back(t); }
    virtual std::vector<T>& allitems() { return items; }
    virtual T get(const uint& i) {/*if (i >= 0 && i < items.size())*/ return items[i];}
    T& operator[](const int& it) {
        return it > 0 ? items[it%size()] : items[size() - (-it)%size()];
    }
    uint size() { return items.size(); }
protected:
    std::vector<T> items;
};

template <typename T>
class List : public Container<T> {
public:
    int index_of(T a) {
        auto it = std::find(this->items.begin(), this->items.end(), a);
        return it != this->items.end() ? it - this->items.begin() : -1;
    }
    
};

template <typename T>
class CycleList : public List<T> {
    uint cursor = 0;
public:
    virtual void next() {
        cycle(1);
    }
    virtual void previous() {
        cycle(-1);
    }
    
    virtual T get() {
        return Container<T>::get(cursor);
    }
    
    virtual void cycle(int i) {
        cursor += i;
        if (cursor < 0) {
            cursor = this->size() - (-cursor)%this->size();
        }
        else if (cursor >= this->size()) {
            cursor = cursor%this->size();
        }
    }
};

#endif // container_hpp__