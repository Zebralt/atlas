#ifndef container_hpp__
#define container_hpp__

template <typename T>
class Container {
public:
    std::vector<T> items;
    virtual void add(T t) { items.push_back(t); }
    std::vector<T>& get() { return items; }
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