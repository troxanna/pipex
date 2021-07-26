#include "includes/pipex.h"

void	check_quotes(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == ' ')
			cmd[i] = '\"';
		if (cmd[i] == '\'')
		{
			cmd[i] = '\"';
			i++;
			while (cmd[i] != '\'' && cmd[i])
				i++;
			if (cmd[i] == '\'')
			{
				cmd[i] = '\"';
				i++;
			}
			else
				ft_error(7, NULL);
		}
	}
}

void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

int	check_equals_sign(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '=' && argv[i] != '\0')
		i++;
	return (i);
}

void	ft_error_exec(int id, char *cmd, t_args *args)
{
	dup2(args->fd, args->fd_out);
	write(args->fd, "\033[1m" ANSI_COLOR_RED "", 10);
	if (id == 2)
	{
		ft_putstr_fd(cmd, args->fd);
		ft_putstr_fd(": command not found", args->fd);
		ft_putchar_fd('\n', args->fd);
	}
	else if (id == 3)
	{
		args->err_code = -1;
		ft_putstr_fd(cmd, args->fd);
		ft_putstr_fd(": no such file or directory", args->fd);
		ft_putchar_fd('\n', args->fd);
	}
	else if (id == 6)
	{
		ft_putstr_fd(cmd, args->fd);
		ft_putstr_fd(": permission denied\n", args->fd);
	}
	exit(args->err_code);
}

void	ft_error(int id, char *cmd)
{
	write(1, "\033[1m" ANSI_COLOR_RED "", 10);
	if (id == 1)
	{
		ft_putstr_fd("malloc error", 1);
		ft_putchar_fd('\n', 1);
	}
	else if (id == 4)
	{
		ft_putstr_fd("too many arguments", 1);
		ft_putchar_fd('\n', 1);
	}
	else if (id == 5)
	{
		ft_putstr_fd("not enough arguments", 1);
		ft_putchar_fd('\n', 1);
	}
	else if (id == 7)
	{
		ft_putstr_fd("unclosed quotes", 1);
		ft_putchar_fd('\n', 1);
	}
	exit(1);
}
