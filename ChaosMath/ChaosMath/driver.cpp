#include <iostream>

#include "ChaosMath.h"

int main() {
	// test perpendicular
	cm::vec2f x0;
	cm::vec2f x1(1);
	cm::vec2f x2(1, 2);
	cm::vec2f x3(x2);

	std::cout << x0 << std::endl;
	std::cout << x1 << std::endl;
	std::cout << x2 << std::endl;
	std::cout << x3 << std::endl;

	cm::vec3f y4(x3);

	std::cout << y4 << std::endl;

	cm::vec4f v0;
	cm::vec4f v1(1);
	cm::vec4f v2(1, 2, 3, 4);
	cm::vec4f v3(v2);

	cm::vec4f t1(31, 96, -48, 15);
	cm::vec4f t2(-72, 14, -33, -57);

	//std::cout << (vec2f)v3 << std::endl;
	//std::cout << (vec3f)x3 << std::endl;
	//std::cout << (vec4f)y3 << std::endl;

	return 0;
}