/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:34:19 by sunko             #+#    #+#             */
/*   Updated: 2023/10/31 13:51:57 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "source.h"
# include "../minishell.h"

# define INIT_SRC_POS	-1
# define ERRCHAR		0

typedef enum e_token_list
{
	LOGICAL_END,
	LOGICAL_OR,
	WILDCARD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	LEFT_PAREN,
	RIGHT_PAREN,
	RIGHT_REDIR,
	LEFT_REDIR,
	RIGHT_APPEND,
	LEFT_APPEND,
	DOLLAR_SIGN,
	WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*string;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
	t_token	*cur;
	int		num_of_data;
}	t_token_list;

typedef struct s_source
{
	char	*buffer;	/* the input text */
	int		bufsize;	/* size of the input text */
	int		curpos;		/* absolute char postion in source */
}	t_source;

/* tokenizer.c */
t_token_list	*tokenizer(t_token_list *token_list, t_source *src);
void			ampersand_token(t_token_list *list, t_source *src);
void			pipe_logical_or_token(t_token_list *list, t_source *src);
void			quotes_token(t_token_list *list, t_source *src, char cur);
void			asterisk_token(t_token_list *list);

/* tokenizer_util.c */
void			left_redirection_token(t_token_list *list, t_source *src, char cur);
void			right_redirection_token(t_token_list *list, t_source *src, char cur);
void			word_token(t_token_list *list, t_source *src, char cur);
void			parentheses_token(t_token_list *list, char cur);
int				ft_is_not_word(char c);

/* token.c */
t_token			*create_token(void);
void			token_push_back(t_token_list *list, t_token *token);
t_token_list	*create_token_list(void);
size_t			find_close_quote(char *str);
size_t			find_next_space(char *str);



#endif

