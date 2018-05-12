#include "progress_bar_animation.hpp"
#include "../ui/progressbar.hpp"
#include "../graphic_obj.hpp"

/// PROGRESS BAR SPECIFIC ANIMAION

ProgressBarAnimation::ProgressBarAnimation(ProgressBar* pgb, float value, int interval,int wait) : Animation(interval,wait) {
    this->pgb = pgb;
    this->value = value;
}

void ProgressBarAnimation::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now - past >= interval) {
        int v = 5;
        past = now;
        if (value+v >= pgb->getValue() && value-v <= pgb->getValue()) {
            pgb->setValue(value);
            status = TERMINATED;
        }
        else {
            if (pgb->getValue() > value) {
                pgb->setValue(pgb->getValue()-v);
            }
            else {
                pgb->setValue(pgb->getValue()+v);
            }
        }
    }
}