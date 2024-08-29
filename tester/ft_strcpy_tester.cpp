#include "tester.hpp"

void test_strcpy(const char *src) {
	char dest1[100];
	char dest2[100];
	std::cout << std::endl;
	std::cout << "src :      \"" << src << "\"" << std::endl;
	strcpy(dest1, src);
	std::cout << "strcpy :   \"" << dest1 << "\"" << std::endl;
	ft_strcpy(dest2, src);
	std::cout << "ft_strcpy :\"" << dest2 << "\"" << std::endl;
}
