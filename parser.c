
#include "includes/pipex.h"

int	parser(char **argv, char **env, int argc)
{
	t_args	*args;

	args = ft_init_args(env);
	args->fd_in = open(argv[1], O_RDONLY, 0644);
	if (args->fd_in == -1)
		ft_error_exec(3, argv[1], args);
	args->fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	args->cmd = create_cmd(argv, argc - 3, 2, 0);
	if (argc == 4)
	{
		dup_fd_start(args->fd_out, args->fd_in);
		exec_run(args, args->cmd->cmd);
	}
	else
		execute_pipe(args);
	return (1);
}
