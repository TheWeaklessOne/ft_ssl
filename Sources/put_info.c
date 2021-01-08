#include "ft_ssl.h"

static void			put_commands(void)
{
	register int	i;
	const int		max = COMMANDS_N - 1;

	i = -1;
	while (++i < max)
		ft_putendl_fd(get_commands()[i], 2);
}

void				put_info(const char *command)
{
	if (!command)
		return ;
	ft_putstr_fd("ft_ssl: Error: '", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("' is an invalid command.", 2);
	ft_putendl_fd("\nStandard commands:", 2);
	ft_putstr_fd("", 2);
	ft_putendl_fd("\nMessage Digest commands:", 2);
	put_commands();
	ft_putendl_fd("\nCipher commands:", 2);
	ft_putendl_fd("", 2);
}
