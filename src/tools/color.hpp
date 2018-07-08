#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <SFML/Graphics/Color.hpp>

// namespace atlas_engine {
//namespace Tools {

sf::Color darker(const sf::Color& c, int offset = 10);
sf::Color brighter(const sf::Color& c, int offset = 10);

//} 
// } // namespace Tools

#endif // COLOR_HPP_