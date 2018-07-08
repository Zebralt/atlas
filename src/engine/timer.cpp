#include "timer.hpp"

// namespace atlas_engine {

void Timer::stop() {
	status = 0;
	// I added those because there were some margins. 
	deadTime = sf::milliseconds(-3);
	pauseTime = sf::Time();
}

void Timer::play() {
	if (status == 0) {				
		status = 1;
		clock.restart();
	}
}

void Timer::pause() {
	if (status == 1) {
		status = 2;
		pauseTime = clock.getElapsedTime();
	}
}

void Timer::unpause() {
	if (status == 2) {
		deadTime += clock.getElapsedTime() - pauseTime;
		status = 1;	
	// I added those because there were some margins. 
		deadTime -= sf::milliseconds(2);
	}
}

void Timer::toggle_pause() {
	if (status == 2) {
		unpause();
	}
	else if (status == 1) {
		pause();
	}
}

void Timer::reset() {
	stop();
	play();
}

sf::Time Timer::time() {
	if (status == 1) {
		return clock.getElapsedTime() - deadTime;
	}
	else if (status == 2) {
		return pauseTime;
	}
	else {
		return sf::Time();
	}
}

int Timer::as_milliseconds() {
	return time().asMilliseconds();
}

// } // namespace atlas_engine