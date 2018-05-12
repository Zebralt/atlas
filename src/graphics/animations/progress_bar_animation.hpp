#ifndef PROGRESS_BAR_ANIMATION_HPP_
#define PROGRESS_BAR_ANIMATION_HPP_

#include "../animation.hpp"


class ProgressBar;

class ProgressBarAnimation : public Animation {
public:
    ProgressBarAnimation(ProgressBar* pb, float value, int interval, int wait = 0);
    void update();
private:
    ProgressBar* pgb;
    float value;
};

#endif // PROGRESS_BAR_ANIMATION_HPP_