NAME = minishell
CC = cc
CFLAGS = -g
READLINE_FLAG = -lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include/readline
LIBFT_FLAG = -L$(LIB_PATH) -l$(LIB)
LIB_PATH = libft
LIB = ft
SRCS = signal/signal.c\
	   terminal/terminal.c\
	   error/error.c\
	   executor/executor.c\
	   executor/command.c\
	   executor/executor_util.c\
	   executor/simple_command.c\
	   parser/parser.c\
	   parser/parser_token.c\
	   token/source.c\
	   token/token.c\
	   token/tokenizer.c\
	   token/tokenizer_util.c\
	   util/get_shell_name.c\
	   util/ft_malloc.c\
	   debug_tool.c\
	   minishell.c
OBJS = $(SRCS:.c=.o)
HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	$(CC) $(CFLAGS) -o $@ $^ -I $(HEADER) $(READLINE_FLAG) $(LIBFT_FLAG)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C ./libft clean
	rm -f $(OBJS)

fclean:
	@make -C ./libft fclean
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re



