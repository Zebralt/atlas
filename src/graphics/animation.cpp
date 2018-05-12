#include <iostream>
#include <sstream>

#include "animation.hpp"
#include "graphic_obj.hpp"

/// ANIMATION

Animation::Animation(int interval, int wait) {
    this->interval = interval;
    past = wait;
    status = RUNNING;
}

bool Animation::isRunning() {
    return status == RUNNING;
}

int Animation::getPast() {
    return past;
}

/// WAIT AND BE STILL

WaitAndBeStill::WaitAndBeStill(Blob* w, int wait) : Animation(0,wait) {

}

void WaitAndBeStill::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now >= past) {
        status = TERMINATED;
    }
}
