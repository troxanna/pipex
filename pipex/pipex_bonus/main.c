#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 5 && !ft_strncmp(argv[1], "here_doc",
			ft_strlen(argv[1]) > 8 ? ft_strlen(argv[1]) : 8))
		ft_error(5, NULL);
	if (argc < 4)
		ft_error(5, NULL);
	else if (!ft_strncmp(argv[1], "here_doc",
			ft_strlen(argv[1]) > 8 ? ft_strlen(argv[1]) : 8))
		limiter_read(argc, argv, env);
	else
		parser(argv, env, argc);
	return (0);
}