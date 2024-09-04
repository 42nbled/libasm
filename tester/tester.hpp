#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <iomanip>
#include <cstdarg>

#ifndef TESTER_HPP
#define TESTER_HPP

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
//   TEST
// ------------------------------------------------

void	test_strlen(const char *str);
void	test_strcmp(const char *s1, const char *s2);
void 	test_strcpy(const char *src);
void 	test_write(const char *str, int fd);
void 	test_read(const char *filename, int flag);
void 	test_strdup(const char *str);
void 	test_ft_atoi_base(std::string str, std::string base);

// ------------------------------------------------
//   UTILS
// ------------------------------------------------

void 	print_header(const char* str);
void 	init_list(t_list** head, const std::string& type, int count, ...);
void 	print_list(t_list* head, void (*print_data)(void*));
void 	print_int(void* data);
void 	print_str(void* data);
long	diff_int(void *a, void *b);
long	diff_str(void *a, void *b);
char	*allocate_string(const char* str);
void 	lst_free(t_list *a);
void 	lst_free_malloc(t_list *a);
void 	ft_free(void *data);
void 	ft_free_nothing(void *data);
int    	ft_strcmp(void *data1, void *data2);
int    	ft_intcmp(void *data1, void *data2);
int		is_equal_int(void *data1, void *data2);
int		is_equal_str(void *data1, void *data2);

#endif
