#include "../includes/pipex.h"

static void	check_limiter_word(char **argv)
{
	char	*line;
	int		fd_tmp;
	int		read;

	fd_tmp = open("input_tmp", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777);
	while (1)
	{
		write(1, "\033[1m" ANSI_COLOR_CYAN "", 10);
		write(1, "heredoc> ", 10);
		write(1, "\033[1m" ANSI_COLOR_RESET "", 9);
		read = get_next_line(0, &line);
		if (!ft_strncmp(line, argv[2], ft_strlen(line)
				> ft_strlen(argv[2]) ? ft_strlen(line) : ft_strlen(argv[2])))
			break ;
		write(fd_tmp, line, ft_strlen(line));
		free(line);
		ft_putchar_fd('\n', fd_tmp);
	}
	free(line);
	close(fd_tmp);
}

int	limiter_read(int argc, char **argv, char **env)
{
	t_args	*args;

	check_limiter_word(argv);
	args = ft_init_args(env);
	args->fd_in = open("input_tmp", O_RDONLY, 0644);
	if (args->fd_in == -1)
		ft_error_exec(3, NULL, args);
	args->fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	args->cmd = create_cmd(argv, argc - 4, 3, 0);
	if (argc == 5)
	{
		dup_fd_start(args->fd_out, args->fd_in);
		exec_run(args, args->cmd->cmd);
	}
	else
		execute_pipe(args);
	return (1);
}