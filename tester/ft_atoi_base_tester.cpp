#include "tester.hpp"

void test_ft_atoi_base(std::string str, std::string base) {
	char	s[str.length() + 1];
	char	b[base.length() + 1];
	strcpy(s, str.c_str());
	strcpy(b, base.c_str());

	std::cout << std::left; // Align text to the left
    std::cout << "String: \"" << std::setw(15) << str + "\"";
    std::cout << "Base: \"" << std::setw(20) << base + "\"";
	std::cout << "Result: \"";
	std::cout << ft_atoi_base(s, b) << "\"" << std::endl;
}
