#include "includes/pipex.h"
#include <stdio.h>

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

	err_code = execve(bin, cmd, args->env);
	if (err_code == -1)
		ft_error_exec(6, cmd[0]);
}

static char	*exec_case_handling(char **cmd)
{
	char		*bin;
	int	code_err;

	bin = NULL;
	if (!ft_strncmp("./", cmd[0], 2)
		|| !ft_strncmp("../", cmd[0], 3)
		|| !ft_strncmp("/", cmd[0], 1))
	{
		bin = ft_strdup(cmd[0]);
		code_err = access(cmd[0], 0);
		if (code_err == -1)
			ft_error_exec(3, cmd[0]);
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
		ft_error_exec(3, cmd[0]);
	ptr = add_slach_arg(cmd[0]);
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
		ft_error_exec(2, cmd[0]);
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
