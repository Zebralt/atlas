#ifndef ANIMATION_GROUP_HPP_
#define ANIMATION_GROUP_HPP_

#include "../animation.hpp"


class AnimationGroup : public Animation {
public:
	AnimationGroup(int wait = 0);
	void update();
	void addAnimation(Animation* a);
private:
	std::vector<Animation*> animations;
};


#endif // GROUP_ANIMATION_HPP_