#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

/** Macros, typenames and functions common to all files.
*/

#include <iostream>

/// MACROS
#define print(x) std::cout << x
#define println(x) print(x) << std::endl
#define PRINT(x) print(x)
#define PRINTLN(x) println(x)
#define LOG(x) println(x)

/// TYPENAMES

/// FUNCTIONS

/// STRUCTS

struct Size {
	int w,h;
	Size() {w = h = 0;}
	Size(int a, int b) : w(a), h(b) {}
};

#endif // GLOBAL_HPP_