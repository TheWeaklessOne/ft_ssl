#include "ft_ssl.h"

static char		*command_generator(const char *text, int state)
{
	static int	i;
	static int	len;
	char		*name;
	const char	*upper = ft_str_to_upper(text);
	char		**strings;

	strings = (char**)(hash_type_names + 1);
	if (!state)
	{
		i = 0;
		len = ft_strlen(text);
	}
	while (strings[i] && (name = strings[i]))
	{
		++i;
		if (!ft_strcmp(name, hash_type_names[HASH_TYPES_N]))
			continue;
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

void			initialize_readline(void)
{
	rl_readline_name = "ft_ssl";
	rl_attempted_completion_function = ash_complition;
}
