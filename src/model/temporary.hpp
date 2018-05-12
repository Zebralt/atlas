#ifndef temporary_hpp__
#define temporary_hpp__

#define TERMINATED  0
#define RUNNING     1
#define IDLE        2

class Temporary {
protected:
    short status = 1;
public:
    Temporary() {}
    virtual short getStatus() { return status; }
    virtual void setStatus(short s) { status = s;}

    virtual void update() = 0;
};

#endif
