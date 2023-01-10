#include <string.h>
#include <stdio.h>
/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (diff);
}
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s10;
	unsigned char	*s20;

	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	while ((*s10 || *s20) && n--)
		if (*s10++ != *s20++)
			return (*(--s10) - *(--s20));
	return (0);
}


int	main(void)
{
	printf("ft_strncmp:: %d \n", ft_strncmp("azul\0awen", "azul", 15));
	printf("   strncmp:: %d \n", strncmp("azul-awen", "azul", 15));
	return (0);
}
