#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

# define ANSI_COLOR_RED "\x1b[31m"

typedef	struct s_cmd
{
	char **cmd;
	struct s_cmd	*next;
}				t_cmd;

typedef	struct s_args
{
	int	fd_out;
	int	fd_in;
	t_cmd	*cmd;
	char	**env;
}				t_args;

void	ft_error(int id, char *cmd);
void	free_array(void **array);
void	exec_run(t_args *args, char **cmd);
void	execute_pipe(t_args *args);


#endif