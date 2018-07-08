#include <iostream>
#include <sstream>
#include <cmath>

#include "animation.hpp"
#include "graphic_obj.hpp"

#include "tools/vector2_operators.hpp"

#define compute_offset(a, b) (b - a)/float(duration * float(1000/Engine::update_interval))

/// ANIMATION

// namespace atlas_engine {
//namespace Graphics {


Animation::Animation(float duration, int wait, int interval) {
    this->interval = interval;
    this->duration = duration;
    past = wait;
    status = RUNNING;
}

bool Animation::isRunning() {
    return status == RUNNING;
}

int Animation::getPast() {
    return past;
}

/// BASE ANIMATION MODELS
Action::Action(float duration, int wait, int interval) : Animation(duration, wait, interval) {}

void Action::set_target(Blob* target) {
	this->target = target;
}

TextAnimation::TextAnimation(float duration, int wait, int interval) : Action(duration, wait, interval) {}

void TextAnimation::set_target(Label* target) {
	this->target = (Blob*) target;
}

/// FADEIN
FadeIn::FadeIn(float duration, int wait, int interval) : Action(duration, wait, interval) {}
void FadeIn::update() {
	int now = timer.as_milliseconds();
	if (status == RUNNING && now - past >= interval) {
		if (target && target->getOpacity() > 0) {
			target->setOpacity(target->getOpacity() + compute_offset(target->getOpacity(), 0) - 1);
		}
		else {
			TERMINATE;
		}
		past = now;
	}
}

/// FADEOUT
FadeOut::FadeOut(float duration, int wait, int interval) : Action(duration, wait, interval) {}
void FadeOut::update() {
	int now = timer.as_milliseconds();
	if (status == RUNNING && now - past >= interval) {
		if (target && target->getOpacity() < 255) {
			target->setOpacity(target->getOpacity() + compute_offset(target->getOpacity(), 255) + 1);
		}
		else {
			TERMINATE;
		}
		past = now;
	}
}

/// DOKE
Move::Move(const Vec2& data, float duration, int wait, int interval) : Action(duration, wait, interval) {
	this->vec = Vec2f(data);
	this->factors = Vec2f(vec.x < 0 ? -1 : 1, vec.y < 0 ? -1 : 1);
	this->vec = this->factors * this->vec;
	this->buffer = vec;
}

// int for the speed or float for the accuracy ?
void Move::update() {
	int now = timer.as_milliseconds();
	if (status == RUNNING && now - past >= interval) {
		if (target && (buffer.x != 0 || buffer.y != 0)) {
//			uint rx = 1 + trunc(compute_offset(0, vec.x));
//			uint ry = 1 + trunc(compute_offset(0, vec.y));
//			uint dx, dy;
			float rx = compute_offset(0, vec.x);
			float ry = compute_offset(0, vec.y);
			float dx, dy;

			buffer.x -= (dx = buffer.x > rx ? rx : buffer.x);
			buffer.y -= (dy = buffer.y > ry ? ry : buffer.y);
			target->setPosition(target->getPosition() + factors * Vec2f(dx, dy));
		}
		else {
			TERMINATE;
		}
		past = now;
	}
}

GoTo::GoTo(const Vec2& data, float duration, int wait, int interval) : Move(data, duration, wait, interval) {
	this->vec = Vec2f(data);
}

void GoTo::set_target(Blob* target) {
	Action::set_target(target);
	buffer = vec - target->getPosition();
	vec = buffer;
	this->factors = Vec2f(vec.x < 0 ? -1 : 1, vec.y < 0 ? -1 : 1);
	this->vec = this->factors * this->vec;
	this->buffer = vec;
	
}

Sequence::Sequence(float duration, int wait, int interval) : Action(duration, wait, interval) {}
Sequence::Sequence(const std::vector<Action*>& elems, float duration, int wait, int interval) : Action(duration, wait, interval) {
	addAll(elems);
}

void Sequence::update() {
	int now = timer.as_milliseconds();
	if (status == RUNNING) {
		if (now - past > interval) {
			if (it < size()) {
				if (items[it] && items[it]->getStatus()) {
					items[it]->update();
				}
				else {
					_FREE(items[it]);
					++it;
					if (it >= size()) TERMINATE;
					else if (items[it]) now += items[it]->getPast();
				}
			}
			else TERMINATE;
			past = now;
		}
	}
}

void Sequence::set_target(Blob* target) {
	Action::set_target(target);
	
	for (auto item : items) {
		if (item) {
			item->set_target(target);
		}
	}
}

/// WAIT AND BE STILL

//WaitAndBeStill::WaitAndBeStill(Blob* w, int wait) : Animation(0,wait) {
//
//}
//
//void WaitAndBeStill::update() {
//    int now = clock.getElapsedTime().asMilliseconds();
//    if (isRunning() && now >= past) {
//        status = TERMINATED;
//    }
//}


//} 
// } // namespace Video