#include "ft_ssl.h"

static void put_info(const char *command)
{
	ft_putstr_fd("ft_ssl: Error: '", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("' is an invalid command.", 2);
	ft_putendl_fd("\nStandard commands:", 2);
	ft_putstr_fd("", 2);
	ft_putendl_fd("\nMessage Digest commands:", 2);
	ft_putendl_fd("md5\nsha256\n", 2);
	ft_putendl_fd("\nCipher commands:", 2);
	ft_putendl_fd("", 2);
}

int			check_command(const char *command)
{
	int		type;

	type = 0;
	if (!ft_strcmp(command, "md5"))
		type = IS_MD5;
	else if (!ft_strcmp(command, "sha256"))
		type = IS_SHA256;
	return (type);
}

int			main(int argc, char *argv[])
{
	t_ssl	ssl;
	char	*command;

	if (argc < 2)
		return (ft_putstr_fd("usage: ft_ssl command [command opts] [command args]", 1));
	command = ft_strdup(argv[1]);
	while (!(ssl.type = check_command(command)))
	{
		put_info(argv[1]);
		free(command);
		command = readline("ft_ssl>");
	}
	return (0);
}
