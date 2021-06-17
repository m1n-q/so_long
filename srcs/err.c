#include "so_long.h"

void	err(void)
{
	perror("Error\nso_long");
	exit(errno);
}

void	myerr(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(errno);
}