#include "animation_sequence.hpp"
#include "../graphic_obj.hpp"

/// GROUP ANIMATION

AnimationSequence::AnimationSequence(int wait) : Animation(0,wait) {

}

void AnimationSequence::addAnimation(Animation* a) {
    animations.push_back(a);
}

void AnimationSequence::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now - past >= interval) {
        past = now;
        if (animations[it]->isRunning()) {
            animations[it]->update();
        }
        else {
            it++;
            if (it >= animations.size()){
                status = TERMINATED;
                return;
            }
            past += animations[it]->getPast();
        }
    }
}

AnimationSequence::~AnimationSequence() {
	for (int i=0;i<animations.size();i++) {
		delete(animations[i]);
	}
}