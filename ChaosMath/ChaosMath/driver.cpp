#include <iostream>

#include "cm.h"

int main() {
	cm::vec4f v;
	cm::vec4f v1(1);
	cm::vec4f v2(1, 2, 3, 4);
	cm::vec4f v3(v);


	std::cout << v2.x << ", " << v2.y << ", " << v2.z << ", " << v2.w << std::endl;
	std::cout << v3.x << ", " << v3.y << ", " << v3.z << ", " << v3.w << std::endl;

	v2 = v3;

	std::cout << v2.x << ", " << v2.y << ", " << v2.z << ", " << v2.w << std::endl;
	std::cout << v3.x << ", " << v3.y << ", " << v3.z << ", " << v3.w << std::endl;

	std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.w << std::endl;
	std::cout << v1.x << ", " << v1.y << ", " << v1.z << ", " << v1.w << std::endl;

	v.swap(v1);
	std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.w << std::endl;
	std::cout << v1.x << ", " << v1.y << ", " << v1.z << ", " << v1.w << std::endl;

	return 0;
}