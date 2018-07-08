#include "color.hpp"

// namespace atlas_engine {
//namespace Tools {

sf::Color darker(const sf::Color& c, int offset) {
	return sf::Color(c.r - offset, c.g - offset, c.b - offset, c.a);
}

sf::Color brighter(const sf::Color& c, int offset) {
	return sf::Color(c.r + offset, c.g + offset, c.b + offset, c.a);
}

//}
// } // namespace Tools