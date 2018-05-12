#ifndef TIMER_HPP_
#define TIMER_HPP_


#include <SFML/System/Clock.hpp>

/// \brief pause enabled clock
class Timer {
public:
	sf::Clock clock;
	int status = 1; // 0 : stop, 1 : running, 2 : paused
	sf::Time deadTime;
	sf::Time pauseTime;
	Timer() {}
	void stop() {
		status = 0;
		deadTime = sf::milliseconds(-3);
		pauseTime = sf::Time();
	}
	
	void play() {
		if (status == 0) {				
			status = 1;
			clock.restart();
		}
	}
	
	void pause() {
		if (status == 1) {
			status = 2;
			pauseTime = clock.getElapsedTime();
		}
	}
	
	void unpause() {
		if (status == 2) {
			deadTime += clock.getElapsedTime() - pauseTime;
			status = 1;	
			deadTime -= sf::milliseconds(2);
		}
	}
	
	void reset() {
		stop();
		play();
	}
	
	sf::Time getTime() {
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
};

class TimeEnabled {
public:
	Timer timer;
	int past;
	virtual void start() { timer.reset(); }
	virtual void pause() { timer.pause(); }
	virtual void unpause() { timer.unpause(); }
};

#endif // TIMER_HPP_