#include "includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 4)
		ft_error(5, NULL);
	else if (argc > 5)
		ft_error(4, NULL);
	else
		parser(argv, env, argc);
	return (0);
}
