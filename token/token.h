/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:34:19 by sunko             #+#    #+#             */
/*   Updated: 2023/10/27 11:12:38 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../minishell.h"

# define TOKEN_NUM			18
// # define LOGICAL_END		0
// # define LOGICAL_OR			1
// # define SIGLE_QUOTE		3
// # define DOUBLE_QUOTE		4
// # define PIPE				5
// # define LEFR_PAREN			6
// # define RIGHT_PAREN		7
// # define RIGHT_REDIR		13
// # define LEFT_REDIR			14
// # define RIGHT_APPEND		15
// # define LEFT_APPEND		16

typedef enum e_token_list
{
	LOGICAL_END,
	LOGICAL_OR,
	WILDCARD,
	SIGLE_QUOTE,
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


#endif

