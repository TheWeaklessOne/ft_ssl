#include "ft_ssl.h"

static char		*command_generator(const char *text, int state)
{
	static int	i;
	static int	len;
	char		*name;
	const char	*upper = ft_str_to_upper(text);

	if (!state)
	{
		i = 0;
		len = ft_strlen(text);
	}
	while (get_commands()[i] && (name = (char*)get_commands()[i]))
	{
		i++;
		if (ft_strncmp(name, (void*)upper, len) == 0)
		{
			free((void*)upper);
			return (ft_strdup(name));
		}
	}
	free((void*)upper);
	return ((char *)NULL);
}

static char		**ash_complition(const char *text, int start, int end)
{
	char		**matches;

	matches = NULL;
	(void)end;
	if (start == 0)
		matches = rl_completion_matches(text, command_generator);
	return (matches);
}

void		initialize_readline(void)
{
	rl_readline_name = "ft_ssl";
	rl_attempted_completion_function = ash_complition;
}