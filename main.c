#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct s_list {
    struct s_list *next;
    void *data;
} t_list;

// ------------------------------------------------
//   FT_LIST_PUSH_FRONT
// ------------------------------------------------

void	ft_list_push_front(t_list **begin_list, void *data) {
    t_list *a = malloc(sizeof(t_list));
    if (!a) {
        perror("Failed to create node");
        exit(EXIT_FAILURE);
    }
    a->next = *begin_list;
    a->data = data;
    *begin_list = a;
}

// ------------------------------------------------
//   FT_LIST_SIZE
// ------------------------------------------------

int	ft_list_size(t_list *begin_list)
{
	if (begin_list == NULL)
		return 0;
	if (begin_list->next)
		return(ft_list_size(begin_list->next) + 1);
	return 1;
}

// ------------------------------------------------
//   FT_LIST_UTILS
// ------------------------------------------------

void	init_list(t_list **head, char *type, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        if (type == "int") {  // Integer type
            int *value = (int *)malloc(sizeof(int));
            if (!value) {
                perror("Failed to allocate memory for value");
                exit(EXIT_FAILURE);
            }
            *value = va_arg(args, int);
            ft_list_push_front(head, value);
        } else if (type == "str") {  // String type
            char *str = va_arg(args, char *);
            char *value = strdup(str);  // Duplicate the string to allocate memory
            if (!value) {
                perror("Failed to allocate memory for string");
                exit(EXIT_FAILURE);
            }
            ft_list_push_front(head, value);
        }
    }

    va_end(args);
}

void	print_list(t_list *head, void (*print_data)(void *)) {
    t_list *temp = head;
    while (temp != NULL) {
        print_data(temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void	print_int(void *data) {
    printf("%d -> ", *(int *)data);
}

void	print_str(void *data) {
    printf("%s ", (char *)data);
}

int	diff_int(t_list *a, t_list *b) {
    if (!a || !a->data)
		return 0;
	if (!b || !b->data)
		return 0;
	int *data_a = (int *)a->data;
    int *data_b = (int *)b->data;

    return (*data_a - *data_b);
}

int	diff_str(t_list *a, t_list *b) {
    if (!a || !a->data)
		return 0;
	if (!b || !b->data)
		return 0;
    char *data_a = (char *)a->data;
    char *data_b = (char *)b->data;

    return strcmp(data_a, data_b);
}

void lst_free(t_list *a)
{
	while (a)
	{
    	if (a->data)
			free(a->data);
		t_list *b = a->next;
		free(a);
		a = b;
	}
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

// ------------------------------------------------
//   FT_LIST_SORT
// ------------------------------------------------

void ft_swap(t_list **a, t_list **b) {
	t_list *c = *a;
	*a = *b;
	*b = c;
}

void ft_lst_swap(t_list **header, t_list *a, t_list *b) {
	if (a == b)
		return;
	if (a == NULL || b == NULL)
		return;

	t_list **first = header;
	while (*first && *first != a)
		first = &(*first)->next;

	t_list **second = header;
	while (*second && *second != b)
		second = &(*second)->next;

	ft_swap(first, second);
	ft_swap(&(*first)->next, &(*second)->next);
}

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	if (!begin_list)
		return;
	if (!*begin_list)
		return;

	t_list *a;
	t_list *b;
	t_list *c;
	t_list *d;
	a = *begin_list;

	while (a && a->next)
	{
		b = a->next;
		c = a;
		while (b)
		{
			if (cmp(c, b) > 0) {
				c = b;
			}
			b = b->next;
		}
		d = a->next;
		ft_lst_swap(begin_list, a, c);
		a = d;
	}
}

// ------------------------------------------------
//   FT_LIST_REMOVE_IF
// ------------------------------------------------

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
{
    t_list *current;
    t_list *prev;
    t_list *temp;

    while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
    {
        temp = *begin_list;
        *begin_list = (*begin_list)->next;
        free_fct(temp->data);
        free(temp);
    }

    prev = *begin_list;
    if (prev == NULL)
        return;

    current = prev->next;

    while (current)
    {
        if (cmp(current->data, data_ref) == 0)
        {
            prev->next = current->next;
            free_fct(current->data);
            free(current);
            current = prev->next;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

// ------------------------------------------------
//   MAIN
// ------------------------------------------------

int main() {
    t_list *nbr = NULL;
    t_list *str = NULL;

    // Initialize the list with the given values
	printf("##Initializing int list##\n");
	init_list(&nbr, "int", 10, 7, 4, 6, 3, 8, 4, 7, 4, 1, 2);
	printf("##Initializing string list##\n");
	init_list(&str, "str", 5, "amet", "sit", "dolor", "ipsum,", "lorem");

    // // Print the lists
	printf("\n");
	printf("int list    = ");
    print_list(nbr, print_int);
	printf("string list = ");
    print_list(str, print_str);

	// // Print lists size
	printf("\n");
	printf("Size of nbr list : %d\n", ft_list_size(nbr));
	printf("Size of str list : %d\n", ft_list_size(str));

	// // Sort the lists
	printf("\n");
	printf("before sort : ");
	print_list(nbr, print_int);
	ft_list_sort(&nbr, diff_int);
	printf("after sort  : ");
	print_list(nbr, print_int);
	printf("\n");
	printf("before sort : ");
	print_list(str, print_str);
	ft_list_sort(&str, diff_str);
	printf("after sort  : ");
	print_list(str, print_str);

	// Remove if
	printf("\n");
	int		a = 3;
    void	*tmp = &a;
	printf("##Removing 3 in int list##\n");
    ft_list_remove_if(&nbr, tmp, ft_intcmp, ft_free);

    // Remove strings
    char 	*b = "sit";
    tmp = b;
	printf("##Removing sit in string list##\n");
    ft_list_remove_if(&str, tmp, ft_strcmp, ft_free);

	// // Print the lists
	printf("\n");
	printf("int list    = ");
    print_list(nbr, print_int);
	printf("string list = ");
    print_list(str, print_str);

    // Free the allocated memory
	lst_free(nbr);
	lst_free(str);

    return 0;
}
