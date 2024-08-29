#include "tester.hpp"

void test_write(const char *str, int fd) {
	std::cout << "write :" << std::endl;
	ssize_t bytes_written = write(fd, str, ft_strlen(str));
	int a = errno;
	std::cout << "(" << bytes_written << "l)" << std::endl;
	std::cout << "ft_write :" << std::endl;
	bytes_written = ft_write(fd, str, ft_strlen(str));
	int b = errno;
	std::cout << "(" << bytes_written << "l)" << std::endl << std::endl;
	std::cout << "write errno = "<< a << std::endl;
	std::cout << "ft_write errno = "<< b << std::endl;
}
