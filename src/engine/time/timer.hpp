#ifndef TIMER_HPP_
#define TIMER_HPP_


#include <SFML/System/Clock.hpp>

/**
	\author Zebralt
	\brief This is a class is built atop the class Clock provided by the SFML.
	It allows for pausing, which is not provided by Clock.
*/
class Timer {
public:
	Timer() {}
	
	/// \brief Stops the timer and resets it.
	void stop();
	
	/// \brief Restarts the timer.
	void play();
	
	/// \brief Pauses the timer. Time at pause is conserved.
	void pause();
	
	/// \brief Unpauses the timer. To be used after being paused, otherwise, no effect.
	void unpause();
	
	/// \brief Resets the timer to 0. It keeps ticking.
	void reset();
	
	/// \brief Allows to switch between Pause and Playing.
	void toggle_pause();
	
	/// \brief Tells the time.
	sf::Time time();
	
	
	/// \brief Tells the time but IN SPACE ! I mean, in milliseconds.
	int as_milliseconds();
	
	/// \brief Returns timer's status, if you ever need it.
	/// 0 for stopped, 1 for running, 2 for paused.
	int getStatus() { return status; }
	
private:
	sf::Clock clock;
	int status = 1; // 0 : stop, 1 : running, 2 : paused
	sf::Time deadTime;
	sf::Time pauseTime;

};

#include <map>
#include <string>

/**
	\author Zebralt
	\brief This class is to serve as a base class for all time related objects.
	All classes that require to analyze and keep track of the passage of time
	can inherit from this class. As you may need more than one time tracker, 
	the default being the 'past' variable, you can use the 'timers' interface
	to store them by name.
*/
class TimeEnabled {
public:
	
	/// \brief Resets the timer.
	virtual void reset() { timer.reset(); }
	
	/// \brief Pauses the timer.
	virtual void pause() { timer.pause(); }
	
	/// \brief Unpauses the timer.
	virtual void unpause() { timer.unpause(); }
	
	/// \brief I guess you could just use Timer::toggle_pause now.
	virtual void toggle_pause() { timer.getStatus() == 1 ? timer.pause() : timer.unpause(); }
	
	/// \brief Creates or sets a timer.
	void set_timer(const std::string& name, int i) { timers[name] = i; }
	
	/// \brief Creates a timer and assign current time in milliseconds to it.
	void create_timer(const std::string& name) { timers[name] = timer.as_milliseconds(); }
	
	/// \brief Returns a timer given its registration name.
	int get_timer(const std::string& name) { return timers.find(name) != timers.end() ? timers[name] : 0; }
	
private:
	std::map<std::string, int> timers;
	
protected:
	Timer timer;
	int past;
};

#endif // TIMER_HPP_