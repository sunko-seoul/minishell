/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:24:19 by sunko             #+#    #+#             */
/*   Updated: 2023/11/06 16:07:17 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../token/token.h"
# include "../minishell.h"


typedef struct s_tree
{
	struct s_tree_token	*root;
	struct s_tree_token	*first_child;
	struct s_tree_token *last_child;
	struct s_tree_token *cur;
}	t_tree;

typedef struct s_tree_token
{
	t_token_type		type;
	char				*value;
	struct s_tree_token	*next;
	struct s_tree_token	*child;
}	t_tree_token;


/* parser.c */
void	next_sym(t_token_list *list);
int		sym_accept(t_token_list *list, t_token_type type);
int		sym_expect(t_token_list *list, t_token_type type);
void	add_child(t_tree *tree, t_tree_token *new_tok);
void	add_next(t_tree_token *child_tok, t_tree_token *new_tok);

/* parser_token.c */
void	parse_pipe(t_token_list *list, t_tree *tree);
void	parse_logical(t_token_list *list, t_tree *tree);
void	parse_quote(t_token_list *list, t_tree *tree);
void	parse_paren(t_token_list *list, t_tree *tree);
void	parse_command(t_token_list *list, t_tree *tree);
void	parse_redir(t_token_list *list, t_tree *tree);

int	tree_check_type(t_tree_token *tree_tok, t_token_type type);

#endif
