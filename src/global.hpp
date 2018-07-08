#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

/** Macros, typenames and functions common to all files.
*/

#include <iostream>
#include <SFML/Graphics/Rect.hpp>

//#include "tools/vector2_operators.hpp"

/// MACROS
#define PRINT(x) std::cout << x
#define PRINTLN(x) PRINT(x) << std::endl
#define println(x) PRINT(x) << std::endl
#define LOG(x) PRINTLN(x)

 #define _FREE(a) if (a) delete a

/// TYPENAMES

typedef unsigned int uint;
typedef sf::IntRect Rect;
typedef sf::Vector2f Vec2f;
typedef sf::Vector2i Vec2;

template <typename T> class ptr_vector : public std::vector<T*> {};

/// FUNCTIONS
template <typename T> std::ostream& operator<<(std::ostream& o, const sf::Vector2<T>& v) {
	return o << "vec(" << v.x << ", " << v.y << ")";
}

struct cmpVec2i {
	bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) {
		return a.x * 10 + a.y < b.x * 10 + b.y;
	}
};

/// STRUCTS

struct Size {
	int w,h;
	Size() {w = h = 0;}
	Size(int a, int b) : w(a), h(b) {}
};

#endif // GLOBAL_HPP_