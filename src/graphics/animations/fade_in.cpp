#include "fade_in.hpp"
#include "../graphic_obj.hpp"

/// FADE IN

FadeIn::FadeIn(Blob* w, int interval,int f,int wait) : Animation(interval,wait) {
    this->target = w;
    thresh = f;
}

void FadeIn::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now  - past >= interval) {
        if (target->getOpacity() > thresh) {
            (*target).setOpacity(target->getOpacity()-10);
            //std::cout << "FadeIn::still here ..." << target->getOpacity() << std::endl;
        }
        else {
            status = TERMINATED;
        }
        past = now;
    }
}