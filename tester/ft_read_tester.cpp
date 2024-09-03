#include "tester.hpp"

void test_read(const char *filename, int flag) {
	std::cout << std::endl;
	std::cout << "\033[1mFILENAME: " << filename << "\033[0m" << std::endl;
	int fd = open(filename, flag);
	if (fd < 0)
		return;
	char buffer1[100];
	ssize_t bytes_read = read(fd, buffer1, sizeof(buffer1) - 1);
	int a = errno;
	buffer1[bytes_read] = '\0';
	std::cout << std::endl;
	std::cout << "read from \"" << filename << "\" :" << std::endl;
	std::cout << "\"" << buffer1 << "\"\n (" << bytes_read << " b)" << std::endl;
	close(fd);
	fd = open(filename, flag);
	if (fd < 0)
		return;
	char buffer2[100];
	bytes_read = ft_read(fd, buffer2, sizeof(buffer2) - 1);
	int b = errno;
	buffer2[bytes_read] = '\0';
	std::cout << std::endl;
	std::cout << "ft_read from \"" << filename << "\" :" << std::endl;
	std::cout << "\"" << buffer2 << "\"\n (" << bytes_read << " b)" << std::endl << std::endl;
	std::cout << "read errno =    "<< a << std::endl;
	std::cout << "ft_read errno = "<< b << std::endl;
	close(fd);
	std::cout << std::endl;
}
