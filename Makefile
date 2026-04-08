# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smayunga <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/03 22:19:27 by smayunga          #+#    #+#              #
#    Updated: 2026/03/16 13:38:59 by smayunga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell
LIBFT   = libft
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
LIBFTFLG = -L$(LIBFT) -lft -lreadline

OBJDIR  = objs

SRCS    =	srcs/main.c \
			srcs/setup_sign.c \
			srcs/free_resource.c \
			srcs/env/env_core.c \
			srcs/env/env_ops.c \
			srcs/parser/expand.c \
			srcs/parser/lexeme.c \
			srcs/parser/parser.c \
			srcs/execute/execute_promptl.c \
			srcs/execute/run_builtin.c \
			srcs/execute/redir_heredoc.c \
			srcs/builtins/builtin_cd.c \
			srcs/builtins/builtin_echo.c \
			srcs/builtins/builtin_env.c \
			srcs/builtins/builtin_exit.c \
			srcs/builtins/builtin_export.c \
			srcs/builtins/builtin_pwd.c \
			srcs/builtins/builtin_unset.c \
			srcs/utils/utils_ext0.c

OBJS    = $(patsubst srcs/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)
$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)/
	$(CC) $(OBJS) $(LIBFTFLG) -o $@
$(OBJDIR)/%.o: srcs/%.c mshell.h utils.h | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -iquote . -iquote $(LIBFT)/ -c $< -o $@

$(OBJDIR):
	mkdir -p $@

.PHONY: all clean fclean re

clean:
	rm -fr $(OBJDIR)
	$(MAKE) -C $(LIBFT)/ clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT)/ fclean

re: fclean all
