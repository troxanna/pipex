#include "includes/pipex.h"

void	dup_fd_start(int fd_out, int fd_in)
{
	close(1);
	dup2(fd_out, 1);
	close(0);
	dup2(fd_in, 0);
}

int	count_pipe(t_cmd *cmd)
{
	t_cmd	*ptr;
	int			i;

	i = 0;
	ptr = cmd;
	while (cmd->next)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	**create_pipe_fd(int count)
{
	int		**fd;
	int		i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * count + 1);
	fd[count] = NULL;
	while (i < count)
		fd[i++] = (int *)malloc(sizeof(int) * 2);
	return (fd);
}
