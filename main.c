#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct s_list
{
	struct s_list *next;
	void *data;
} t_list;

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list *a = malloc(sizeof(t_list));
	a->next = *begin_list;
	a->data = data;
	*begin_list = a;
}

int main()
{
	t_list a = {0};
	t_list b = {0, .next = &a};
	t_list *c = &b;
	ft_list_push_front(&c, (void *)123);
	printf("%d\n", (int)c->data);
	return 0;
}
