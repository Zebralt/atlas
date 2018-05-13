#ifndef pellet_factory_hpp
#define pellet_factory_hpp

#include <string>
#include <sstream>
#include <vector>
#include <SFML/System/Vector2.hpp>

/**
	\author Me.
	\brief This file contains all the functions that aid in generating level content.
*/

/*
sample bullet wave:

<time>:<type>:<speed>:<pattern>:<angle>

base position is vertical.

example : 5 by 5 bullets in a 90° arc every 1 second.

-- arc
0:simple:1:linear:-45
0:simple:1:linear:-22
0:simple:1:linear:0
0:simple:1:linear:22.5
0:simple:1:linear:45

-- arc
1000:simple:1:linear:-45
1000:simple:1:linear:-22.5
1000:simple:1:linear:0
1000:simple:1:linear:22.5
1000:simple:1:linear:45

let's make a bullet wave factory :

instant-arc:
	*startAngle = -45
	*spanAngle = 90 (-45 to 45)
	*nb_projectiles = 5
	-- (thus angle between two projectiles = starAngle + spanAngle/nb_projectiles)
	nb_waves (repeat x times)
	period -- between two waves of projectiles

sprinkle-arc:
	startAngle -- = -45
	lengthAngle -- = 90
	period -- between two projectiles
	*/

struct PelletSample {
	std::string desc;
	int time;
};

//int getTimeFromRaw(std::string str) {
//	return std::stoi(split(str,':')[0]);
//}

/// an element of content associated with its timing
typedef std::pair<int, std::string> timed_pair;

/// a list of timed elements
typedef std::vector<timed_pair> timedList;

/**
	\class Meta data of a wave
	\brief figures a wave model	
*/	
class RawWave {
public:
	RawWave();
	RawWave(timedList tl);
	
	timedList content; ///< the list of timed items
	int it = 0; ///< the iterator to circulate through the wave
	int time = -1; ///< cache stamp of last time reached
	
	/// \brief add a timed item
	/// \param ti is the time
	/// \param str is the item
	void add(int ti, std::string str); 
	
	std::string& operator[](int i);
	
	/// \brief merge a rawwave into this one (their lists)
	void merge(RawWave& bw);
	
	void merge(RawWave* bw);
	
	void merge(timedList tl);
	
	/// \brief sort the timed list by time (bubble sort)
	void sort();
	
	/// \brief retrieve the next time to wait for
	int getNextTime();
	
	/// \brief indicates if the wave has ended ( => end of wave)
	bool eow();
	
	/// \brief return a list of all the elements timeset to time parameter
	/// \param t is the time parameter
	std::vector<std::string> getByTime(int t);
	
	/// \brief resets timestamp and iterator
	void reset();
};


std::string getPatternName(int t);

/*
:sample vessel wave:

<time>:<type>:<speed>:<pattern>

idea: how about mobile objs intro ?
- classic coming from outscreen
- "classy" teleportation"
- hyperspeed from the side/top

*/

namespace vessel_factory {
	
	/// \brief generates a timed list of vessel foes going along a straight line
	timedList createLine(
	sf::Vector2f startPoint,
	float angle,
	short nb_vessels,
	short pattern_type,
	short type,
	float speed,
	int period,
	int delay
	);
	
}

namespace event_factory {
		
	/// \brief generates an event
	std::string createEvent(
	std::string name,
	std::string animations,
	int duration,
	int delay
	);
	
}

/// generate bullets lists
/// look at data.txt and above
	
namespace pellet_factory {
	
	/// \brief generates a serie of bullet shots : this function generates <nb_waves> arcs of <nb_projectiles> projectiles every <period> milliseconds \
	/// arc spans from startAngle (ex:-90) to endAngle (startAngle + spanAngle(180) = 90) ; bullets angle equally divided by their number
	timedList createInstantArc(
	float startAngle, 
	float spanAngle,
	short nb_projectiles,
	short type,
	short pattern_type,
	float speed,
	short nb_waves,
	int period,
	int delay
	);
	
	/// \brief generates a wave of X bullets sprinkling along an arc
	/// \param swing indicates if it has to act like a pendulum or just start over from startAngle once it has reached the end of the arc
	timedList createSprinkleArc(
	float startAngle, 
	float spanAngle,
	short nb_projectiles,
	short nb_per_arc,
	short type,
	short pattern_type,
	short speed,
	int period,
	bool swing,
	int delay
	);
	
}	
	
#endif // pellet_factory_hpp
