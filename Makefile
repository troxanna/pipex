# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kshanti <kshanti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/01 19:12:24 by kshanti           #+#    #+#              #
#    Updated: 2021/07/05 19:17:26 by kshanti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

HEAD = ./includes/
SRCS_BONUS = ./bonus/
GNL = ./get_next_line/

CFLAGS = -Wall -Wextra -Werror

C_FILE = $(GNL)get_next_line.c $(GNL)get_next_line_utils.c utils.c exec_command.c pipe.c utils_pipe.c init.c parser.c

C_FILE_MAIN = main.c $(C_FILE)

C_FILE_BONUS = ./pipex_bonus/main.c ./pipex_bonus/limiter.c $(C_FILE)

O_FILE = $(C_FILE_MAIN:.c=.o)

O_FILE_BONUS = $(C_FILE_BONUS:.c=.o)

all:
	$(MAKE) $(NAME) -j 4

$(NAME): $(O_FILE)
	$(MAKE) -C ./libft bonus
	gcc $(O_FILE) ./libft/libft.a -o $(NAME)

%.o: %.c $(HEAD)
	gcc -c $(СFLAGS) $< -o $@

bonus: $(O_FILE_BONUS)
	$(MAKE) -C ./libft bonus
	gcc $(O_FILE_BONUS) ./libft/libft.a -o $(NAME)

clean:
	@rm -f $(O_FILE)
	$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
