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

template <typename T> void update_or_delete( std::vector<T*>& items) {
	for (auto it = items.begin(); it != items.end();) {
        if ((*it)->getStatus()) {
            (*it)->update();
        }
        else {
            delete *it;
            it = items.erase(it);
            continue;
        }
        
        ++it;
    }
}

#endif
