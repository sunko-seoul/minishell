/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:34:19 by sunko             #+#    #+#             */
/*   Updated: 2023/08/05 12:14:52 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../minishell.h"

# define TOKEN_NUM			18
# define LOGICAL_END		0
# define LOGICAL_OR			1
# define SIGLE_QUOTE		3
# define DOUBLE_QUOTE		4
# define PIPE				5
# define LEFR_PAREN			6
# define RIGHT_PAREN		7
# define RIGHT_REDIR		13
# define LEFT_REDIR			14
# define RIGHT_APPEND		15
# define LEFT_APPEND		16

typedef enum e_token_list
{
	logical_end,
	logical_or,
	wildcard,
	s_quote,
	d_quote,
	t_pipe,
	left_paren,
	right_paren,
	left_brace,
	right_brace,
	left_braket,
	right_braket,
	semi_colon,
	right_redir,
	left_redir,
	right_append,
	left_append,
	dollar_sign
}	t_token_type;

typedef struct s_token
{
	t_token_type type;
	char	*string;
}	t_token;

typedef struct s_node
{
	t_token			*token;
	struct s_node	*next;
}	t_node;

typedef struct s_token_list
{
	t_node	*head;
	t_node	*tail;
	t_node	*cur;
	int		num_of_data;
}	t_token_list;

/* quote_scan.c */
int				get_quote_len(char *string, char quote);
char			*quote_malloc(int len);
void			sigle_quote_scan(t_token_list *list, char *command, size_t *i);
void			double_quote_scan(t_token_list *list, char *command, size_t *i);

/* scan.c */
t_token			scan(char *command);

/* token_list.c */
t_node			*create_node(void);
t_token_list	*create_token_list(void);
t_token			*create_token_sample(void);
void			push_back(t_token_list *token_list, t_node *node);

/* init_token.c */
void			init_token(t_token *token_list);

#endif

