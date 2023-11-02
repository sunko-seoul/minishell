/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:24:19 by sunko             #+#    #+#             */
/*   Updated: 2023/11/02 23:30:09 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token/token.h"
#include "../minishell.h"


typedef struct s_tree
{
	struct s_tree_token	*root;
	struct s_tree_token	*first_child;
	struct s_tree_token *last_child;
}	t_tree;

typedef struct s_tree_token
{
	t_token_type		type;
	char				*value;
	struct s_tree_token	*next;
	struct s_tree_token	*child;
}	t_tree_token;

void	next_sym(t_token_list *list);
int		sym_accept(t_token_list *list, t_token_type type);
int		sym_expect(t_token_list *list, t_token_type type);
