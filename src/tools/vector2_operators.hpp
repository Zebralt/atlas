#ifndef VEC2_OPERATORS_HPP_
#define VEC2_OPERATORS_HPP_

#include <SFML/System/Vector2.hpp>

template<typename T> sf::Vector2<T> operator*(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
	return sf::Vector2<T>(v.x * w.x, v.y * w.y);
}

//template<typename T> bool operator<(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
//	return v.x < w.x && v.y < w.y;
//}
//
//template<typename T> sf::Vector2<T> operator>(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
//	return v.x > w.x && v.y > w.y;
//}
//
//template<typename T> sf::Vector2<T> operator<=(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
//	return v.x <= v.y && w.x <= w.y;
//}
//
//template<typename T> sf::Vector2<T> operator>=(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
//	return v.x >= v.y && w.x >= w.y;
//}
//
//template<typename T> sf::Vector2<T> operator+(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
//	return sf::Vector2<T>(v.x + w.x, v.y + w.y);
//}
//
//template<typename T> sf::Vector2<T> operator-(const sf::Vector2<T>& v, const sf::Vector2<T>& w) {
//	return sf::Vector2<T>(v.x - w.x, v.y - w.y);
//}

#endif // VEC2_OPERATORS_HPP_