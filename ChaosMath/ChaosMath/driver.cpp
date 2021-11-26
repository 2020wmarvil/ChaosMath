#include <iostream>

#include "ChaosMath.h"

int main() {
	cm::vec4f v0;
	cm::vec4f v1(1);
	cm::vec4f v2(1, 2, 3, 4);
	cm::vec4f v3(v2);

	cm::vec4f t1(31, 96, -48, 15);
	cm::vec4f t2(-72, 14, -33, -57);

	std::cout << cm::vec4f::Normalize(t1) << std::endl;
	std::cout << cm::vec4f::Normalize(t2) << std::endl;
	std::cout << cm::vec4f::Scale(t1, t2) << std::endl;
	std::cout << cm::vec4f::Scale(t2, t1) << std::endl;

	return 0;
}