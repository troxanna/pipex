#include "includes/pipex.h"
#include <stdio.h>

static char	*get_env_char(char **env, char *str)
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

static char	*exec_case_handling(char **cmd, t_args *args)
{
	char		*bin;

	bin = NULL;
	if (!ft_strncmp("./", cmd[0], 2)
		|| !ft_strncmp("../", cmd[0], 3)
		|| !ft_strncmp("/", cmd[0], 1))
	{
		bin = ft_strdup(cmd[0]);
		args->err_code = access(cmd[0], 0);
		if (args->err_code == -1)
			ft_error_exec(3, cmd[0], args);
	}
	return (bin);
}

static char	*exec_find_handling(t_args *args, char **cmd)
{
	char		**path;
	int			i;
	char		*ptr;
	char		*bin;

	ptr = get_env_char(args->env, "PATH");
	path = ft_split(ptr, ':');
	if (!ptr || !path)
		ft_error_exec(3, cmd[0], args);
	ptr = add_slach_arg(cmd[0]);
	i = -1;
	while (path[++i])
	{
		bin = ft_strjoin(path[i], ptr);
		args->err_code = access(bin, 0);
		if (args->err_code != -1)
			break ;
		free(bin);
	}
	free_array((void **)path);
	free(ptr);
	if (args->err_code == -1)
		ft_error_exec(2, cmd[0], args);
	return (bin);
}

void	exec_run(t_args *args, char **cmd)
{
	char	*bin;

	
	bin = exec_case_handling(cmd, args);
	if (!bin)
		bin = exec_find_handling(args, cmd);
	if (bin)
	{
		args->err_code = execve(bin, cmd, args->env);
		if (args->err_code == -1)
			ft_error_exec(6, cmd[0], args);
		free(bin);
	}
}
