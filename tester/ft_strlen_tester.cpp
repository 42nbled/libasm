#include "tester.hpp"

void	test_strlen(const char *str) {
	std::cout << std::endl;
	std::cout << "str :      \"" << str << "\"" << std::endl;
	std::cout << "strlen :   \"" << strlen(str) << "\"" << std::endl;
	std::cout << "ft_strlen :\"" << ft_strlen(str) << "\"" << std::endl;
}
