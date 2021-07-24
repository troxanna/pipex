#include "includes/pipex.h"
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

void	add_cmd(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*ptr;

	ptr = *cmd;
	if (*cmd == NULL)
		*cmd = new_cmd;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_cmd;
	}
}

t_args	*ft_init_args(char **env, int fd_in, int fd_out, int count)
{
	t_args	*args;
	int	i;

	i = 0;
	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
		ft_error(1, NULL);
	args->fd_in = fd_in;
	args->fd_out = fd_out;
	args->env = env;
	args->cmd = NULL;
}

int		parser(char **argv, char **env, int argc)
{
	t_args	*args;
	int		fd_out;
	int		fd_in;
	int		i;
	int		j;
	char	*tmp;
	t_cmd	*ptr;

	fd_in = open(argv[1], O_RDONLY, 0644);
	fd_out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_in == -1)
		ft_error(3, argv[1]);
	args = ft_init_args(env, fd_in, fd_out, argc - 3);
	i = 0;
	args->cmd = new_cmd();
	while (++i < argc - 3)
	{
		add_cmd(&(args->cmd), new_cmd());
		//printf("%d\n", i);
	}
	ptr = args->cmd->next;
	printf("%p\n", ptr->next);
	i = -1;
	j = 2;
	while (ptr && ++i < argc - 3)
	{
		tmp = ft_strdup(argv[j]);
		//ptr->cmd = ft_split(tmp, ' ');
		free(tmp);
		j++;
		//ptr = ptr->next;
	}
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	if (argc < 5)
		ft_error(5, NULL);
	else if (argc > 5)
		ft_error(4, NULL);
	else
		parser(argv, env, argc);
}
