#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
	ssize_t ft_write(int fd, const void *buf, size_t nbyte);
	ssize_t ft_read(int fd, void *buf, size_t nbyte);
	int     ft_strlen(const char *str);
	int     ft_strcmp(const char *s1, const char *s2);
	char    *ft_strcpy(char *dst, const char *src);
	char    *ft_strdup(const char *s1);
	// BONUS
	int     ft_atoi_base(char *str, char *base);
}

void	test_strlen(const char *str) {
	std::cout << std::endl;
	std::cout << "str :      \"" << str << "\"" << std::endl;
	std::cout << "strlen :   \"" << strlen(str) << "\"" << std::endl;
	std::cout << "ft_strlen :\"" << ft_strlen(str) << "\"" << std::endl;
}

void	test_strcmp(const char *s1, const char *s2) {
	std::cout << std::endl;
	std::cout << "s1 :       \"" << s1 << "\"" << std::endl;
	std::cout << "s2 :       \"" << s2 << "\"" << std::endl;
	int result = strcmp(s1,s2);
	std::cout << "strcmp :   \"" << result << "\"" << std::endl;
	result = ft_strcmp(s1,s2);
	std::cout << "ft_strcmp :\"" << result << "\"" << std::endl;
}

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

void test_write(const char *str) {
	std::cout << "write :" << std::endl;
	ssize_t bytes_written = write(STDOUT_FILENO, str, ft_strlen(str));
	std::cout << "(" << bytes_written << "l)" << std::endl;
	std::cout << "ft_write :" << std::endl;
	bytes_written = ft_write(STDOUT_FILENO, str, ft_strlen(str));
	std::cout << "(" << bytes_written << "l)" << std::endl << std::endl;
}

void test_read(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		std::cerr << "Error opening file for reading: " << filename << std::endl;
		return;
	}
	char buffer1[100];
	ssize_t bytes_read = read(fd, buffer1, sizeof(buffer1) - 1);
	if (bytes_read == -1) {
		std::cerr << "Error reading file: " << filename << std::endl;
		close(fd);
		return;
	}
	buffer1[bytes_read] = '\0';
	std::cout << std::endl;
	std::cout << "read from \"" << filename << "\" :" << std::endl;
	std::cout << "\"" << buffer1 << "\"\n (" << bytes_read << " b)" << std::endl;
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		std::cerr << "Error opening file for reading: " << filename << std::endl;
		return;
	}
	char buffer2[100];
	bytes_read = ft_read(fd, buffer2, sizeof(buffer2) - 1);
	if (bytes_read == -1) {
		std::cerr << "Error reading file: " << filename << std::endl;
		close(fd);
		return;
	}
	buffer2[bytes_read] = '\0';
	std::cout << std::endl;
	std::cout << "ft_read from \"" << filename << "\" :" << std::endl;
	std::cout << "\"" << buffer2 << "\"\n (" << bytes_read << " b)" << std::endl;
	close(fd);
}

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

int main() {

	std::cout << "base size / NULL"                                     << std::endl;
	std::cout << ft_atoi_base("2147483647", NULL)                       << std::endl;
	std::cout << ft_atoi_base("2147483647", "")                         << std::endl;
	std::cout << ft_atoi_base("2147483647", "0")                        << std::endl;
	std::cout << "double_character_check"                               << std::endl;
	std::cout << ft_atoi_base("2147483647", "01234567890")              << std::endl;
	std::cout << ft_atoi_base("2147483647", "01234556789")              << std::endl;
	std::cout << ft_atoi_base("2147483647", "01234567899")              << std::endl;
	std::cout << "valid_character_check"                                << std::endl;
	std::cout << ft_atoi_base("2147483647", "012345+6789")              << std::endl;
	std::cout << ft_atoi_base("2147483647", "012-3456789")              << std::endl;
	std::cout << ft_atoi_base("2147483647", "0123456 789")              << std::endl;
	std::cout << ft_atoi_base("2147483647", "01234    56789")           << std::endl;
	std::cout << "valid"                                                << std::endl;
	std::cout << ft_atoi_base("2147483647", "0123456789")               << std::endl;
	std::cout << ft_atoi_base("           2147483647", "0123456789")    << std::endl;
	std::cout << ft_atoi_base("+2147483647", "0123456789")              << std::endl;
	std::cout << ft_atoi_base("-2147483647", "0123456789")              << std::endl;
	std::cout << ft_atoi_base("+-2147483647", "0123456789")             << std::endl;
	std::cout << ft_atoi_base("--2147483647", "0123456789")             << std::endl;
	std::cout << ft_atoi_base("           +2147483647", "0123456789")   << std::endl;
	std::cout << ft_atoi_base("2147483647", "0123456789")               << std::endl;
	std::cout << ft_atoi_base("A", "ABCDEFGH")                          << std::endl;
	std::cout << ft_atoi_base("BA", "ABCDEFGH")                         << std::endl;
	std::cout << ft_atoi_base("F0", "0123456789ABCDEF")                 << std::endl;
	std::cout << ft_atoi_base("7FFFFFFF", "0123456789ABCDEF")           << std::endl;

	// // Test ft_strlen
	// std::cout << "\033[1mFT_STRLEN\033[0m" << std::endl;
	// test_strlen("");
	// test_strlen("1");
	// test_strlen("42");
	// test_strlen("Hello");
	// test_strlen("Hello World !");
	// std::cout << std::endl;

	// // // Test ft_strcmp
	// std::cout << "\033[1mFT_STRCMP\033[0m" << std::endl;
	// test_strcmp("", "");
	// test_strcmp("", "Hello");
	// test_strcmp("Hello", "");
	// test_strcmp("Hello", "Hello");
	// test_strcmp("Hello", "42");
	// test_strcmp("Hello", "Hell");
	// test_strcmp("Hello", "Hello World");
	// std::cout << std::endl;

	// // Test ft_strcpy
	// std::cout << "\033[1mFT_STRCPY\033[0m" << std::endl;
	// test_strcpy("");
	// test_strcpy("42");
	// test_strcpy("Hello");
	// test_strcpy("Hello World!");
	// std::cout << std::endl;

	// // Test ft_write
	// std::cout << "\033[1mFT_WRITE\033[0m" << std::endl;
	// test_write("Hello, ft_write!\n");
	// test_write("Another string for ft_write.\n");
	// std::cout << std::endl;

	// // Test ft_read
	// std::cout << "\033[1mFT_READ\033[0m" << std::endl;
	// test_read("Makefile");
	// std::cout << std::endl;

	// // Test ft_strdup
	// std::cout << "\033[1mFT_STRDUP\033[0m" << std::endl;
	// test_strdup("");
	// test_strdup("Hello");
	// test_strdup("This is a test string for ft_strdup.");
	// std::cout << std::endl;



	return 0;
}
