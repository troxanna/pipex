#include "includes/pipex.h"

static void	write_cmd(char *argv, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strdup(argv);
	if (tmp[0] == ' ')
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(": command not found", 1);
		ft_putchar_fd('\n', 1);
	}
	check_quotes(tmp);
	cmd->cmd = ft_split(tmp, '\"');
	free(tmp);
}

static t_cmd	*new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		ft_error(1, NULL);
	new_cmd->cmd = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

static void	add_cmd(t_cmd **cmd, t_cmd *new_cmd,
			void (*wrt)(char *argv, t_cmd *cmd), char *argv)
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
	args->err_code = 0;
	args->fd = dup(1);
	return (args);
}
