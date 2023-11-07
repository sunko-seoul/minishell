/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:24:19 by sunko             #+#    #+#             */
/*   Updated: 2023/11/07 16:39:00 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../token/token.h"
# include "../minishell.h"


typedef struct s_tree
{
	struct s_tree_token	*root;
	struct s_tree_token *cur;
}	t_tree;

typedef struct s_tree_token
{
	t_token_type		type;
	int					is_list;
	union
	{
		char	*value;
		char	**list;
	}	u_value;
	struct s_tree_token	*left;
	struct s_tree_token	*right;
}	t_tree_token;

t_tree			*parser(t_token_list *list, t_tree *tree);
t_tree_token	*pipeline(t_token_list *list);
t_tree_token	*command(t_token_list *list);
t_tree_token	*redirect_list(t_token_list *list);
t_tree_token	*simple_cmd(t_token_list *list);
t_tree_token	*redirect(t_token_list *list);
t_tree_token	*create_cmd_list_token(t_token_list *list, char *value);
t_tree_token	*create_value_token(char *value);
t_tree_token	*create_list_token(char **list);
int				is_redir_type(t_token *tok, t_token_type type);
int				is_cmd_type(t_token *tok, t_token_type type);


#endif
