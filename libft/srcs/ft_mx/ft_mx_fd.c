#include "libft.h"

void	ft_mx_fd(char **s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return;
	while(s && (*s[i] != '\0'))
	{
		write (fd, s, ft_strlen(s[i]));
		i++;
	}
}