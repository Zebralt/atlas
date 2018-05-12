#ifndef object_hpp__
#define object_hpp__

/// IDENTIFICATION CODES :

#define ONHOVER     0b10000
#define ONCLICK     0b01000
#define CONTAINER   0b00100

class Object {
public:
    Object() {}
    virtual int hashcode() { return 0; }
};

#endif // object_hpp__
