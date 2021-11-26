#include <iostream>

#include "ChaosMath.h"

int main() {
	cm::vec4f v0;
	cm::vec4f v1(1);
	cm::vec4f v2(1, 2, 3, 4);
	cm::vec4f v3(v2);

	std::cout << cm::vec4f::right() << std::endl;
	std::cout << cm::vec4f::up() << std::endl;
	std::cout << cm::vec4f::forward() << std::endl;
	std::cout << cm::vec4f::ana() << std::endl;

	std::cout << cm::vec4f::left() << std::endl;
	std::cout << cm::vec4f::down() << std::endl;
	std::cout << cm::vec4f::back() << std::endl;
	std::cout << cm::vec4f::kata() << std::endl;

	return 0;
}