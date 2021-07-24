#include "includes/pipex.h"


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

char	*get_env_char(char **env, char *str)
{
	int		i;
	char	*ptr;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str) > check_equals_sign(env[i])
				? ft_strlen(str) : check_equals_sign(env[i])))
		{
			ptr = env[i];
			return (ptr + (ft_strlen(str) + 1));
		}
	}
	return (NULL);
}

void	ft_error_exec(int id, char *cmd)
{
	if (id == 2)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": command not found", 1);
		ft_putchar_fd('\n', 1);
	}
	else if (id == 3)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": no such file or directory", 1);
		ft_putchar_fd('\n', 1);
	}
	else if (id == 6)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": permission denied\n", 1);
	}
	exit(1);
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
	exit(1);
}