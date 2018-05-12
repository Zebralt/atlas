#ifndef temporary_hpp__
#define temporary_hpp__

enum TemporaryState {
	TERMINATED, RUNNING, IDLE
};

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
