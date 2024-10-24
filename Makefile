NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = minishell.c \
	   minishell_utils.c \
	   init_sh_info.c \
	   syntax.c \
	   tokenizer.c \
	   parser.c \
	   parser_utils.c \
	   traverse_node.c \
	   traverse_node_utils.c \
	   executor.c \
	   executor_utils.c \
	   expansion.c \
	   heredoc.c \
	   wildcard.c \
	   signal.c \
	   env.c \
	   builtin_echo.c \
	   builtin_cd.c \
	   builtin_pwd.c \
	   builtin_export.c \
	   builtin_unset.c \
	   builtin_env.c \
	   builtin_exit.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^ -lreadline

$(LIBFT):
	cd libft && $(MAKE)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c -o $@ $< -I libft

clean:
	$(RM) $(OBJS)
	cd libft && $(MAKE) $@

fclean: clean
	$(RM) $(NAME)
	cd libft && $(MAKE) $@

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re all
