#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <iomanip>
#include <cstdio>
#include <cstdarg>   // For va_list, va_start, va_arg, va_end
#include <vector>    // For linked list simulation
#include <memory>    // For std::shared_ptr

typedef struct s_list
{
	struct s_list *next;
	void *data;
} t_list;

extern "C" {
	ssize_t ft_write(int fd, const void *buf, size_t nbyte);
	ssize_t ft_read(int fd, void *buf, size_t nbyte);
	int     ft_strlen(const char *str);
	int     ft_strcmp(const char *s1, const char *s2);
	char    *ft_strcpy(char *dst, const char *src);
	char    *ft_strdup(const char *s1);
	// BONUS
	int     ft_atoi_base(char *str, char *base);
	void	ft_list_push_front(t_list **begin_list, void *data);
	int 	ft_list_size(t_list *begin_list);
	void 	ft_list_sort(t_list **begin_list, int (*cmp)());
	void 	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
}

// ------------------------------------------------
//   UTILS
// ------------------------------------------------

void print_header(const char* str) {
    std::string text(str);
    size_t text_length = text.length();

    if (text_length % 2 != 0) {
        text += " ";
        text_length++;
    }

    const size_t total_width = 39;
    size_t len = (total_width - 2 - text_length) / 2;

    std::cout << "\033[1m";
    std::cout << std::string(total_width, '#') << std::endl;
    std::cout << "#" << std::string(len, ' ') << text;
	std::cout << std::string(total_width - 2 - len - text_length, ' ');
    std::cout << "#" << std::endl << std::string(total_width, '#') << std::endl;
    std::cout << "\033[0m";
}

// ------------------------------------------------
//   UTILS BONUS
// ------------------------------------------------

void init_list(t_list** head, const std::string& type, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        if (type == "int") {  // Integer type
            int* value = new int(va_arg(args, int));
			// std::cout << value << std::endl;
            ft_list_push_front(head, static_cast<void*>(value));
        } else if (type == "str") {  // String type
            char* str = va_arg(args, char*);
            char* value = strdup(str);  // Duplicate the string to allocate memory
            ft_list_push_front(head, static_cast<void*>(value));
        }
    }

    va_end(args);
}

// Function to print the linked list
void print_list(t_list* head, void (*print_data)(void*)) {
    t_list* temp = head;
    while (temp != nullptr) {
        print_data(temp->data);
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}

// Example print function for integers
void print_int(void* data) {
    std::cout << *(static_cast<int*>(data)) << " -> ";
}

// Example print function for strings
void print_str(void* data) {
    std::cout << static_cast<char*>(data) << " ";
}

long	diff_int(t_list *a, t_list *b) {
    if (!a || !a->data)
		return 0;
	if (!b || !b->data)
		return 0;
	int data_a = *(int *)a->data;
    int data_b = *(int *)b->data;

    return (data_a - data_b);
}

long	diff_str(t_list *a, t_list *b) {
    if (!a || !a->data)
		return 0;
	if (!b || !b->data)
		return 0;
    char *data_a = (char *)a->data;
    char *data_b = (char *)b->data;

    return strcmp(data_a, data_b);
}

void ft_free(void *data)
{
    free(data);
}

int    ft_strcmp(void *data1, void *data2)
{
	return strcmp((char *)data1, (char *)data2);
}

int    ft_intcmp(void *data1, void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

int		is_troie(void *data1, void *data2)
{
	// std::cout << data << std::endl;
	if (*(int *)data1 == 3)
		return 0;
	return 1;
}

// ------------------------------------------------
//   TEST
// ------------------------------------------------

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

// ------------------------------------------------
//   TEST BONUS
// ------------------------------------------------

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

// ------------------------------------------------
//   MAIN
// ------------------------------------------------

int main() {

	// Test ft_strlen
	print_header("FT_STRLEN");
	test_strlen("");
	test_strlen("1");
	test_strlen("42");
	test_strlen("Hello");
	test_strlen("Hello World !");
	std::cout << std::endl;

	// // Test ft_strcmp
	print_header("FT_STRCMP");
	test_strcmp("", "");
	test_strcmp("", "Hello");
	test_strcmp("Hello", "");
	test_strcmp("Hello", "Hello");
	test_strcmp("Hello", "42");
	test_strcmp("Hello", "Hell");
	test_strcmp("Hello", "Hello World");
	std::cout << std::endl;

	// Test ft_strcpy
	print_header("FT_STRCPY");
	test_strcpy("");
	test_strcpy("42");
	test_strcpy("Hello");
	test_strcpy("Hello World!");
	std::cout << std::endl;

	// Test ft_write
	print_header("FT_WRITE");
	test_write("Hello, ft_write!\n");
	test_write("Another string for ft_write.\n");
	std::cout << std::endl;

	// Test ft_read
	print_header("FT_READ");
	test_read("Makefile");
	std::cout << std::endl;

	// Test ft_strdup
	print_header("FT_STRDUP");
	test_strdup("");
	test_strdup("Hello");
	test_strdup("This is a test string for ft_strdup.");
	std::cout << std::endl;

	{	// Test ft_atoi_base
		print_header("FT_ATOI_BASE");
		std::cout << std::endl;
		std::cout << "\033[1mERROR MANAGEMENT\033[0m" << std::endl;
		char	str[11] = "2147483647";
		std::cout << "String: \"2147483647\"    ";
		std::cout << "Base: \"NULL\"               ";
		std::cout << "Result: \"";
		std::cout << ft_atoi_base(str, NULL) << std::endl;
		test_ft_atoi_base("2147483647", "");
		test_ft_atoi_base("2147483647", "0");
		test_ft_atoi_base("2147483647", "01234567890");
		test_ft_atoi_base("2147483647", "01234556789");
		test_ft_atoi_base("2147483647", "01234567899");
		test_ft_atoi_base("2147483647", "012345+6789");
		test_ft_atoi_base("2147483647", "012-3456789");
		test_ft_atoi_base("2147483647", "0123456 789");
		test_ft_atoi_base("2147483647", "01234    56789");
		test_ft_atoi_base("214a7483647", "0123456789");
		std::cout << "\033[1mVALID\033[0m" << std::endl;
		test_ft_atoi_base("2147483647", "0123456789");
		test_ft_atoi_base("   2147483647", "0123456789");
		test_ft_atoi_base("+2147483647", "0123456789");
		test_ft_atoi_base("-2147483647", "0123456789");
		test_ft_atoi_base("+-2147483647", "0123456789");
		test_ft_atoi_base("--2147483647", "0123456789");
		test_ft_atoi_base("  +2147483647", "0123456789");
		test_ft_atoi_base("2147483647", "0123456789");
		test_ft_atoi_base("A", "ABCDEFGH");
		test_ft_atoi_base("BA", "ABCDEFGH");
		test_ft_atoi_base("F0", "0123456789ABCDEF");
		test_ft_atoi_base("7FFFFFFF", "0123456789ABCDEF");
		std::cout << std::endl;
	}

	print_header("FT_LIST_PUSH_FRONT");

	t_list *nbr = NULL;
    t_list *str = NULL;

	// Initialize the list with the given values
	printf("##Initializing int list##\n");
	// init_list(&nbr, "int", 10, 7, 4, 6, 3, 8, 4, 7, 4, 1, 3);
	init_list(&nbr, "int", 4, 3, 1, 3, 3);
	printf("##Initializing string list##\n");
	init_list(&str, "str", 5, "amet", "sit", "dolor", "ipsum,", "lorem");

    // // Print the lists
	printf("\n");
	printf("int list    = ");
    print_list(nbr, print_int);
	printf("string list = ");
    print_list(str, print_str);

	// // // Print lists size
	// printf("\n");
	// printf("Size of nbr list : %d\n", ft_list_size(nbr));
	// printf("Size of str list : %d\n", ft_list_size(str));

	// // Sort the lists
	// printf("\n");
	// printf("before sort : ");
	// print_list(nbr, print_int);
	// ft_list_sort(&nbr, (int (*)())diff_int);
	// printf("after sort  : ");
	// print_list(nbr, print_int);
	// printf("\n");
	// printf("before sort : ");
	// print_list(str, print_str);
	// ft_list_sort(&str, (int (*)())diff_str);
	// printf("after sort  : ");
	// print_list(str, print_str);

	// Remove if
	printf("\n");
	int		a = 3;
    void	*tmp = &a;
	printf("##Removing 3 in int list##\n");
    ft_list_remove_if(&nbr, tmp, (int (*)())is_troie, ft_free);

    // Remove strings
    // char 	*b = "sit";
    // tmp = b;
	// printf("##Removing sit in string list##\n");
    // ft_list_remove_if(&str, tmp, ft_strcmp, ft_free);

    // // Print the lists
	printf("\n");
	printf("int list    = ");
    print_list(nbr, print_int);
	printf("string list = ");
    print_list(str, print_str);

	return 0;
}
