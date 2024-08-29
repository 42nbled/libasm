#include "tester.hpp"

void	test_strcmp(const char *s1, const char *s2) {
	std::cout << std::endl;
	std::cout << "s1 :       \"" << s1 << "\"" << std::endl;
	std::cout << "s2 :       \"" << s2 << "\"" << std::endl;
	int result = strcmp(s1,s2);
	std::cout << "strcmp :   \"" << result << "\"" << std::endl;
	result = ft_strcmp(s1,s2);
	std::cout << "ft_strcmp :\"" << result << "\"" << std::endl;
}
