#include "includes/pipex.h"

static int	count_pipe(t_cmd *cmd)
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

static void	pipe_child(int **fd, int i, int count)
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
	int			status;
    int err_code;
	while (i > -1)
		waitpid(pid[i--], &status, WUNTRACED | WCONTINUED);
	err_code = WEXITSTATUS(status);
	free_array((void **)fd);
}

void	execute_pipe(t_args *args)
{
    int **fd;
    pid_t   *pid;
    t_cmd   *ptr;
    int i;

    fd = create_pipe_fd(count_pipe(args->cmd) + 1);
	ptr = args->cmd;
	pid = (pid_t *)malloc(sizeof(pid_t) * count_pipe(args->cmd));
    // printf("%s\n", args->cmd->cmd[0]);
    //  printf("%s\n", args->cmd->next->cmd[0]);
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
    i = -1;
	while (++i < count_pipe(args->cmd))
		pipe(fd[i]);
	i = -1;
	while (++i < count_pipe(args->cmd) + 1)
	{
		if (fork_start(&pid[i], fd, i) && !pid[i])
		{
           // write(1, "test", 4);
			pipe_child(fd, i, count_pipe(args->cmd));
			exec_run(args, ptr->cmd);
		}
		ptr = ptr->next;
	}
	wait_fork(pid, i, fd);
	free(pid);
}