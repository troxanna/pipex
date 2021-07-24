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
int		count_pipe(t_cmd *cmd);
int		**create_pipe_fd(int count);
void	ft_error_exec(int id, char *cmd);
int		check_equals_sign(char *argv);
void	dup_fd_start(int fd_out, int fd_in);
char	*get_env_char(char **env, char *str);
void	exec_run(t_args *args, char **cmd);
void	execute_pipe(t_args *args);


#endif