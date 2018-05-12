#include "fade_out.hpp"
#include "../graphic_obj.hpp"

/// FADE OUT

FadeOut::FadeOut(Blob* w, int interval, int f, int wait) : Animation(interval,wait) {

    this->target = w;
    thresh = f;
}

void FadeOut::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now  - past >= interval) {
        if (target->getOpacity() < thresh) {
            (*target).setOpacity(target->getOpacity()+10);
//            std::cout << "Fadeout::still here ..." << target->getOpacity() << std::endl;
        }
        else {
            status = TERMINATED;
        }
        past = now;
    }
}