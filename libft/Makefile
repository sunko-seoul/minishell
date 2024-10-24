NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = r
RM = rm -f

SRCS = ft_atoll.c \
	   ft_bzero.c \
	   ft_calloc.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isspace.c \
	   ft_itoa.c \
	   ft_memcpy.c \
	   ft_putchar_fd.c \
	   ft_putendl_fd.c \
	   ft_putstr_fd.c \
	   ft_split.c \
	   ft_strchr.c \
	   ft_strcmp.c \
	   ft_strdup.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlcpy.c \
	   ft_strlen.c \
	   ft_strncmp.c \
	   ft_substr.c \
	   str_bldr.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(NAME)($(OBJS))

(%.o): %.c libft.h
	$(CC) $(CFLAGS) -c -o $% $<
	$(AR) $(ARFLAGS) $@ $%

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re all
