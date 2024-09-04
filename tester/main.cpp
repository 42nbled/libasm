#include "tester.hpp"

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
	test_write("Hello, ft_write!\n", STDOUT_FILENO);
	test_write("Another string for ft_write.\n", STDOUT_FILENO);
	int fd = open("/dev/full", O_RDONLY);
	test_write("Another string for ft_write.\n", fd);
	close(fd);
	std::cout << std::endl;

	// Test ft_read
	print_header("FT_READ");
	test_read("Makefile", O_RDONLY);
	test_read("unreadable.txt", O_WRONLY);

	// Test ft_strdup
	print_header("FT_STRDUP");
	test_strdup("");
	test_strdup("Hello");
	test_strdup("This is a test string for ft_strdup.");
	std::cout << std::endl;

	{
		// Test ft_atoi_base
		print_header("FT_ATOI_BASE");
		std::cout << std::endl;
		std::cout << "\033[1mERROR MANAGEMENT\033[0m" << std::endl;
		char	str[] = "2147483647";
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

	{
		t_list *nbr = NULL;
		t_list *str = NULL;
		t_list *test = NULL;

		// test ft_list_push_front
		print_header("FT_LIST_PUSH_FRONT");
		std::cout << std::endl;
		ft_list_push_front(&nbr, (void*)3);
		ft_list_push_front(&nbr, (void*)5);
		ft_list_push_front(&nbr, (void*)6);
		ft_list_push_front(&nbr, (void*)2);
		ft_list_push_front(&nbr, (void*)9);
		ft_list_push_front(&nbr, (void*)5);
		ft_list_push_front(&nbr, (void*)1);
		ft_list_push_front(&nbr, (void*)4);
		ft_list_push_front(&nbr, (void*)1);
		ft_list_push_front(&nbr, (void*)3);
		ft_list_push_front(&str, (void*)allocate_string("amet"));
		ft_list_push_front(&str, (void*)allocate_string("sit"));
		ft_list_push_front(&str, (void*)allocate_string("dolor"));
		ft_list_push_front(&str, (void*)allocate_string("ipsum,"));
		ft_list_push_front(&str, (void*)allocate_string("lorem"));
		std:: cout << "int list       = ";
		print_list(nbr, print_int);
		std:: cout << "string list    = ";
		print_list(str, print_str);
		std::cout << std::endl;

		// test ft_list_size
		print_header("FT_LIST_SIZE");
		std::cout << std::endl;
		std:: cout << "Size of NULL list : " << ft_list_size(test) << std::endl;
		std:: cout << "Size of nbr list  : " << ft_list_size(nbr) << std::endl;
		std:: cout << "Size of str list  : " << ft_list_size(str) << std::endl;
		std::cout << std::endl;

		// test ft_list_sort
		print_header("FT_LIST_SORT");
		std::cout << std::endl;
		std::cout << "before sort : ";
		print_list(test, print_int);
		ft_list_sort(&test, (int (*)())diff_int);
		std::cout << "after sort  : ";
		print_list(test, print_int);
		std::cout << std::endl;
		std::cout << "before sort : ";
		print_list(nbr, print_int);
		ft_list_sort(&nbr, (int (*)())diff_int);
		std::cout << "after sort  : ";
		print_list(nbr, print_int);
		std::cout << std::endl;
		std::cout << "before sort : ";
		print_list(str, print_str);
		ft_list_sort(&str, (int (*)())diff_str);
		std::cout << "after sort  : ";
		print_list(str, print_str);
		std::cout << std::endl;

		// test ft_list_remove if
		print_header("FT_LIST_REMOVE_IF");
		std::cout << std::endl;

		int		a = 3;
		char	s[] = "sit";
		void	*tmp = &a;

		printf("NULL list    = ");
		print_list(test, print_int);
		printf("##Removing 3 in NULL list##\n");
		ft_list_remove_if(&test, (void*)3, (int (*)())is_equal_int, ft_free_nothing);
		printf("NULL list    = ");
		print_list(test, print_int);
		std::cout << std::endl;

		printf("int list    = ");
		print_list(nbr, print_int);
		printf("##Removing 3 in int list##\n");
		ft_list_remove_if(&nbr, (void*)3, (int (*)())is_equal_int, ft_free_nothing);
		printf("int list    = ");
		print_list(nbr, print_int);
		std::cout << std::endl;

		tmp = s;
		printf("str list    = ");
		print_list(str, print_str);
		printf("##Removing sit in str list##\n");
		ft_list_remove_if(&str, tmp, (int (*)())is_equal_str, ft_free);
		printf("str list    = ");
		print_list(str, print_str);

		lst_free(nbr);
		lst_free_malloc(str);
	}
	std::cout << std::endl;
	return 0;
}
