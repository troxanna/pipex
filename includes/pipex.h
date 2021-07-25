#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN "\x1b[36m"
# define ANSI_COLOR_RESET "\x1b[0m"

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_args
{
	int		fd_out;
	int		fd_in;
	t_cmd	*cmd;
	char	**env;
	int		err_code;
	int		fd;
}				t_args;

void	ft_error(int id, char *cmd);
void	free_array(void **array);
void	check_quotes(char *cmd);
t_cmd	*create_cmd(char **argv, int count, int j, int i);
t_args	*ft_init_args(char **env);
int		count_pipe(t_cmd *cmd);
int		**create_pipe_fd(int count);
void	ft_error_exec(int id, char *cmd, t_args *args);
int		check_equals_sign(char *argv);
void	dup_fd_start(int fd_out, int fd_in);
void	exec_run(t_args *args, char **cmd);
void	execute_pipe(t_args *args);
int		limiter_read(int argc, char **argv, char **env);
int		parser(char **argv, char **env, int argc);

#endif