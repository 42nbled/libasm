#include "tester.hpp"

void test_strdup(const char *str) {
	char *dup = ft_strdup(str);
	if (dup == nullptr) {
		std::cerr << "Error duplicating string: " << str << std::endl;
		return;
	}
	std::cout << std::endl;
	std::cout << "str :      \"" << str << "\"" << std::endl;
	std::cout << "ft_strdup :\"" << dup << "\"" << std::endl;
	free(dup);
}
