#ifndef container_hpp__
#define container_hpp__

#include <vector>
#include <iostream>
#include <algorithm>

typedef unsigned int uint;

/**
    \brief A class referencing multiple items of one type.
*/
template <typename T>
class Collection {
public:
    uint size() { return items.size(); }
protected:
    std::vector<T> items;
};

/**
    \brief A collection of objects with regular access
    (you can add items, remove items, get items).
*/
template <typename T>
class Container : public Collection<T> {
public:
    virtual void add(T t) { this->items.push_back(t); }
    void addAll(const std::vector<T>& elems) { this->items.insert(this->items.end(), elems.begin(), elems.end()); }
    virtual std::vector<T> allitems() const { return this->items; }
    virtual void remove(T t) { 
        auto it = this->items.begin();
        if ((it = std::find(this->items.begin(), this->items.end(), t)) != this->items.end()) 
            this->items.erase(it); 
    }
    virtual T get(const uint& i) const {/*if (i >= 0 && i < this->items.size())*/ return this->items[i];}
//    T& operator[](const int& it) {
//        return it > 0 ? this->items[it%size()] : this->items[size() - (-it)%size()];
//    }
};


/**
    \brief A collection of items with 
    First-in-first-out style access. (So, a stack ?)
*/
template <typename T>
class Stack : public Collection<T> {
public:
    virtual void push(T a) { this->items.push_back(a); }
    virtual T pop() { return this->items.pop_back(), top(); }
    virtual T top() { return this->items[this->items.size() - 1]; }
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
class Cycle {
protected:
    uint cursor = 0;
public:
    virtual void next() { cycle(1); };
    virtual void previous() { cycle(-1); };
    virtual void cycle(int i) {
        cursor += i;
        if (cursor < 0) {
            cursor = this->cycleSize() - (-cursor)%this->cycleSize();
        }
        else if (cursor >= this->cycleSize()) {
            cursor = cursor%this->cycleSize();
        }
    }
    virtual void setCursor(int i) {
        cursor = i;
    }
    virtual T current() = 0;
    virtual int cycleSize() = 0;
};

template <typename T>
class CycleList : public List<T>, public Cycle<T> {
public:
//    virtual void next() {
//        cycle(1);
//    }
//    virtual void previous() {
//        cycle(-1);
//    }
    
    virtual T current() {
        return Container<T>::get(this->cursor);
    }
    
    virtual int cycleSize() {
        return this->size();
    }
    
//    virtual void resetCursor() {
//        cursor = 0;
//    }
    
//    virtual void cycle(int i) {
//        cursor += i;
//        if (cursor < 0) {
//            cursor = this->size() - (-cursor)%this->size();
//        }
//        else if (cursor >= this->size()) {
//            cursor = cursor%this->size();
//        }
//    }
};

#endif // container_hpp__