#include "includes/pipex.h"

void	write_cmd(char *argv, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strdup(argv);
	cmd->cmd = ft_split(tmp, ' ');
	free(tmp);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		ft_error(1, NULL);
	new_cmd->cmd = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_cmd(t_cmd **cmd, t_cmd *new_cmd, void (*wrt)(char *argv, t_cmd *cmd), char *argv)
{
	t_cmd	*ptr;

	ptr = *cmd;
	wrt(argv, new_cmd);
	if (cmd && new_cmd)
	{
		if (*cmd == NULL)
		*cmd = new_cmd;
		else
		{
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new_cmd;
		}
	}
}

t_cmd	*create_cmd(char **argv, int count, int j, int i)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	write_cmd(argv[j], cmd);
	j++;
	while (++i < count)
	{
		add_cmd(&(cmd), new_cmd(), write_cmd, argv[j]);
		j++;
	}
	return (cmd);

}

t_args	*ft_init_args(char **env)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
		ft_error(1, NULL);
	args->fd_in = 0;
	args->fd_out = 1;
	args->env = env;
	args->cmd = NULL;
	return (args);
}

int		parser(char **argv, char **env, int argc)
{
	t_args	*args;

	args = ft_init_args(env);
	args->fd_in = open(argv[1], O_RDONLY, 0644);
	if (args->fd_in == -1)
		ft_error_exec(3, argv[1]);
	args->fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	args->cmd = create_cmd(argv, argc - 3, 2, 0);
	execute_pipe(args);
	return (1);
}

int	limiter_read(int argc, char **argv, char **env)
{
	char	*line;
	int		fd_tmp;
	int		read;
	t_args	*args;

	fd_tmp = open("input_tmp", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777);
	while (1)
	{
		read = get_next_line(0, &line);
		if (!ft_strncmp(line, argv[2], ft_strlen(line) > ft_strlen(argv[2]) ? ft_strlen(line) : ft_strlen(argv[2])))
			break ;
		write(fd_tmp, line, ft_strlen(line));
		free(line);
		ft_putchar_fd('\n', fd_tmp);
	}
	free(line);
	close(fd_tmp);
	args = ft_init_args(env);
	args->fd_in = open("input_tmp", O_RDONLY, 0644);
	if (args->fd_in == -1)
		ft_error_exec(3, NULL);
	args->fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	args->cmd = create_cmd(argv, argc - 4, 3, 0);
	execute_pipe(args);
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	if (argc < 5) 
		ft_error(5, NULL);
	// else if (argc > 5)
	// 	ft_error(4, NULL);
	else if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) > 8 ? ft_strlen(argv[1]) : 8))
		limiter_read(argc, argv, env);
	else
		parser(argv, env, argc);
	
}
