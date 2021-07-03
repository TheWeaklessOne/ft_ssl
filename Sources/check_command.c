#include "ft_ssl.h"

int				check_command(char **argv)
{
	int			type;
	char		*upper;
	int			i;

	type = 0;
	upper = ft_str_to_upper(argv[0]);
	i = 0;
	while (++i < HASH_TYPES_N)
		if (!ft_strcmp(upper, hash_type_names[i]))
		{
			type = i;
			break ;
		}
	free(upper);
	return (type);
}
