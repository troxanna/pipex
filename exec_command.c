#include "includes/pipex.h"

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

static char	*add_slach_arg(char *str)
{
	int		count;
	int		i;
	char	*arg;

	i = 0;
	count = ft_strlen(str);
	arg = malloc(count + 2);
	arg[i] = '/';
	while (str[i])
	{
		arg[i + 1] = str[i];
		i++;
	}
	arg[i + 1] = '\0';
	return (arg);
}

static void	exec_fork(char **cmd, t_args *args, char *bin)
{
	int		err_code;

	if (args->fd_out != 1)
	{
		close(1);
		dup2(args->fd_out, 1);
	}
	if (args->fd_in != 0)
	{
		close(0);
		dup2(args->fd_in, 0);
	}
	// write(1, cmd[0], ft_strlen(cmd[0]));
	// write(1, cmd[1], ft_strlen(cmd[1]));
	err_code = execve(bin, cmd, args->env);
	if (err_code == -1)
		ft_error(6, cmd[0]);
}

static char	*exec_case_handling(char **cmd)
{
	char		*bin;
	int	code_err;
	//struct stat	buff[1];

	bin = NULL;
	if (!ft_strncmp("./", cmd[0], 2)
		|| !ft_strncmp("../", cmd[0], 3)
		|| !ft_strncmp("/", cmd[0], 1))
	{
		bin = ft_strdup(cmd[0]);
		code_err = access(cmd[0], 0);
		if (code_err == -1)
			ft_error(3, cmd[0]);
	}
	return (bin);
}

static char	*exec_find_handling(char **env, char **cmd)
{
	char		**path;
	int			i;
	char		*ptr;
	char		*bin;
	int	code_err;

	ptr = get_env_char(env, "PATH");
	path = ft_split(ptr, ':');
	if (!ptr || !path)
		ft_error(3, cmd[0]);
	ptr = add_slach_arg(cmd[0]);
	//printf("%s\n", ptr);
	i = -1;
	while (path[++i])
	{
		bin = ft_strjoin(path[i], ptr);
		code_err = access(bin, 0);
		if (code_err != -1)
			break ;
		free(bin);
	}
	free_array((void **)path);
	free(ptr);
	if (code_err == -1)
		ft_error(2, cmd[0]);
	return (bin);
}

void	exec_run(t_args *args, char **cmd)
{
	char	*bin;

	bin = exec_case_handling(cmd);
	if (!bin)
		bin = exec_find_handling(args->env, cmd);
	if (bin)
	{
		exec_fork(cmd, args, bin);
		free(bin);
	}
}
