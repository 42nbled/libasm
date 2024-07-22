#include <stdio.h>

int double_character_check(char *base)
{
	int i = 0;
	while (base[i])
	{
		int y = i + 1;
		while (base[y])
		{
			if (base[i] == base[y])
				return 0;
			y++;
		}
		i++;
	}
	return 1;
}

int is_white_space(char c)
{
	if (c == 9)
		return 1;
	if (c == 10)
		return 1;
	if (c == 11)
		return 1;
	if (c == 12)
		return 1;
	if (c == 13)
		return 1;
	if (c == 32)
		return 1;
	return 0;
}

int valid_character_check(char *base)
{
	int i = 0;
	while (base[i])
	{
		if (base[i] == '+')
			return 0;
		if (base[i] == '-')
			return 0;
		if (is_white_space(base[i]))
			return 0;
		i++;
	}
	return 1;
}

char *skip_white_space(char *str)
{
	while (str[0] && is_white_space(str[0]))
		str++;
	return str;   
}

int is_inbase(char c, char *base)
{
	int i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (1);
		i++;
	}
	return(0);
}

int base_size(char *base)
{
	int i = 0;
	while (base[i])
		i++;
	return(i);
}

int ft_atoi_base(char *str, char *base)
{
	if (base == NULL)
		return 0;
	if (!base[0])
		return 0;
	if (!base[1])
		return 0;
	if (!double_character_check(base))
		return 0;
	if (!valid_character_check(base))
		return 0;
	str = skip_white_space(str);
	
	int signe = 1;
	while (str[0] && (str[0] == '+' || str[0] == '-'))
	{
		if (str[0] == '-')
			signe *= -1;
		str++;
	}
	
	int size = base_size(base);

	int result = 0;
	while (str[0])
	{
		int i = 0;
		if (!is_inbase(str[0], base))
			return (0);
		while (base[i])
		{
			if (str[0] == base[i])
			{
				result *= size;
				result += i;
			}
			i++;
		}
		str++;
	}
	result *= signe;

	return result;
}

int main()
{
	printf("base size / NULL\n");
	printf("%d\n", ft_atoi_base("2147483647", NULL));               // base null
	printf("%d\n", ft_atoi_base("2147483647", ""));                 // base vide
	printf("%d\n", ft_atoi_base("2147483647", "0"));                // base taille 1
	printf("double_character_check\n");
	printf("%d\n", ft_atoi_base("2147483647", "01234567890"));      // double_character_check
	printf("%d\n", ft_atoi_base("2147483647", "01234556789"));      // double_character_check
	printf("%d\n", ft_atoi_base("2147483647", "01234567899"));      // double_character_check
	printf("valid_character_check\n");
	printf("%d\n", ft_atoi_base("2147483647", "012345+6789"));      // valid_character_check
	printf("%d\n", ft_atoi_base("2147483647", "012-3456789"));      // valid_character_check
	printf("%d\n", ft_atoi_base("2147483647", "0123456 789"));      // valid_character_check
	printf("%d\n", ft_atoi_base("2147483647", "01234    56789"));   // valid_character_check
	printf("valid\n");
	printf("%d\n", ft_atoi_base("2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("           2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("+2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("-2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("+-2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("--2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("           +2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("2147483647", "0123456789"));
	printf("%d\n", ft_atoi_base("A", "ABCDEFGH"));
	printf("%d\n", ft_atoi_base("BA", "ABCDEFGH"));
	printf("%d\n", ft_atoi_base("F0", "0123456789ABCDEF"));
	printf("%d\n", ft_atoi_base("7FFFFFFF", "0123456789ABCDEF"));

	return 0;
}