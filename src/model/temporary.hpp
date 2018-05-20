#ifndef temporary_hpp__
#define temporary_hpp__

#include "../global.hpp"

#include <vector>
#include <map>

enum TemporaryState {
	TERMINATED, RUNNING, IDLE
};

#define TERMINATE status = TERMINATED

class Temporary {
protected:
    short status = 1;
public:
    Temporary() {}
    virtual short getStatus() { return status; }
    virtual void setStatus(short s) { status = s;}

    virtual void update() = 0;
};

template <typename T> void update_or_delete(std::vector<T*>& items) {
	for (auto it = items.begin(); it != items.end();) {
        if (*it && (*it)->getStatus()) {
            (*it)->update();
        }
        else {
            _FREE(*it);
            it = items.erase(it);
            continue;
        }
        
        ++it;
    }
}

template <typename U, typename T> void update_or_delete(std::map<U, T*>& items) {
	for (auto it = items.begin(); it != items.end();) {
        if (it->second && it->second->getStatus()) {
            it->second->update();
        }
        else {
            _FREE(it->second);
            it = items.erase(it);
            continue;
        }
        
        ++it;
    }
}

#endif
