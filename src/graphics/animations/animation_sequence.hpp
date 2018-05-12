#ifndef ANIMATION_QUEUE_HPP_
#define ANIMATION_QUEUE_HPP_

#include "../animation.hpp"

class AnimationSequence : public Animation {
public:
    AnimationSequence(int wait = 0);
    void update();
    void addAnimation(Animation* a);
	~AnimationSequence();
    
    int getCursor() { return it; }
private:
    std::vector<Animation*> animations;
    int it = 0;
};

#endif // ANIMATION_QUEUE_HPP_