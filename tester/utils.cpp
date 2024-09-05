#include "tester.hpp"

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

void init_list(t_list** head, const std::string& type, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        if (type == "int") {
            int* value = new int(va_arg(args, int));
            ft_list_push_front(head, static_cast<void*>(value));
        } else if (type == "str") {
            char* str = va_arg(args, char*);
            char* value = strdup(str);
            ft_list_push_front(head, static_cast<void*>(value));
        }
    }

    va_end(args);
}

void print_list(t_list* head, void (*print_data)(void*)) {
    t_list* temp = head;
    while (temp != nullptr) {
        print_data(temp->data);
        temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
}

void print_int(void* data) {
    std::cout << *(int*)data << " -> ";
}

void print_str(void* data) {
    std::cout << static_cast<char*>(data) << " ";
}

long	diff_int(void *a, void *b) {
    return (*(int*)a > *(int*)b);
}

long	diff_str(void *a, void *b) {
    return ((char *)a > (char *)b);
}

char* allocate_string(const char* str) {
    size_t len = strlen(str) + 1;
    char* new_str = (char*)malloc(len);
    if (new_str != nullptr) {
        strcpy(new_str, str);
    }
    return new_str;
}

void lst_free(t_list *a)
{
	while (a)
	{
		t_list *b = a->next;
		free(a);
		a = b;
	}
}

void lst_free_malloc(t_list *a)
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

void ft_free_nothing(void *data)
{
    (void)data;
}

int    ft_strcmp(void *data1, void *data2)
{
	return strcmp((char *)data1, (char *)data2);
}

int    ft_intcmp(void *data1, void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

int		is_equal_int(void *data1, void *data2)
{
	if (*(int*)data1 == *(int*)data2)
		return 0;
	return 1;
}

int		is_equal_str(void *data1, void *data2)
{
	if (*(char *)data1 == *(char *)data2)
		return 0;
	return 1;
}
