#ifndef temporary_hpp__
#define temporary_hpp__

#include "global.hpp"

#include <vector>
#include <map>

// namespace atlas_engine {

enum TemporaryState {
	TERMINATED, RUNNING, IDLE
};
//bool running(const TemporaryState& ts) { return ts != TemporaryState::TERMINATED; }
//bool operator!(const TemporaryState& ts) { return running(ts); }

#define TERMINATE status = TERMINATED

class Temporary {
protected:
    short status = TemporaryState::RUNNING;
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
            LOG("deleted temporary");
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
            LOG("deleted temporary");
            it = items.erase(it);
            continue;
        }
        
        ++it;
    }
}

// } // namespace atlas_engine

#endif
