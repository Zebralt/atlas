#include "animation_group.hpp"
#include "../graphic_obj.hpp"

AnimationGroup::AnimationGroup(int wait) : Animation(interval, wait) {
	
}

void AnimationGroup::addAnimation(Animation* a) {
	animations.push_back(a);
}

void AnimationGroup::update() {
	int now = clock.getElapsedTime().asMilliseconds();
	if (isRunning() && now - past >= interval) {
		// todo
	}
}