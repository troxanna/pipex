#include "includes/pipex.h"

static void	pipe_child(int **fd, int i, int count, int fd_out)
{
	if (i == 0)
	{
		close(fd[i][0]);
		dup2(fd[i][1], 1);
	}
	else if (i < count)
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], 0);
		close(fd[i][0]);
		dup2(fd[i][1], 1);
	}
	else
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], 0);
	}	
}

static int	fork_start(int *pid, int **fd, int i)
{
	*pid = fork();
	if (*pid != 0)
		close(fd[i][1]);
	return (1);
}

static void	wait_fork(pid_t *pid, int i, int **fd)
{
	int	status;
	int	err_code;

	while (pid[i])
		waitpid(pid[--i], &status, WUNTRACED | WCONTINUED);
	err_code = WEXITSTATUS(status);
	if (err_code)
		exit(1);
	free_array((void **)fd);
}

void	execute_pipe(t_args *args)
{
	int		**fd;
	pid_t	*pid;
	t_cmd	*ptr;
	int		i;

	fd = create_pipe_fd(count_pipe(args->cmd) + 1);
	ptr = args->cmd;
	pid = (pid_t *)malloc(sizeof(pid_t) * count_pipe(args->cmd) + 1);
	dup_fd_start(args->fd_out, args->fd_in);
	i = -1;
	while (++i < count_pipe(args->cmd))
		pipe(fd[i]);
	i = -1;
	while (++i < count_pipe(args->cmd) + 1)
	{
		if (fork_start(&pid[i], fd, i) && !pid[i])
		{
			pipe_child(fd, i, count_pipe(args->cmd), args->fd_out);
			exec_run(args, ptr->cmd);
		}
		ptr = ptr->next;
	}
	wait_fork(pid, i, fd);
	free(pid);
}
