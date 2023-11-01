/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:24:19 by sunko             #+#    #+#             */
/*   Updated: 2023/11/01 23:29:33 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token/token.h"
#include "../minishell.h"


typedef struct s_assignment_word
{
	char	*left;
	char	*right;
}	t_assignment_word;

typedef struct s_redirect
{
	int		fd_num;
	char	*type;  // Redirection type: ">", "<", ">>", "<<" etc.
	char	*file_name;
}	t_redirect;

typedef struct s_here
{
	char	*type;  // "<<" etc.
	char	*eof;
}	t_heredoc;

typedef struct s_sipme_cmd
{
	char	*cmd;
	char	*argv[];
}	t_simple_cmd;

typedef struct s_cmd
{
	t_redirect		redirection;
	t_simple_cmd	simple_cmd;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd	command;
	struct 	s_pipe	*next;
}	t_pipe;

typedef struct s_tree
{
	struct s_tree_token	*root;
}	t_tree;

typedef struct s_tree_token
{
	t_token_type	type;
	void			*value;
	struct s_tree_token	*next;
	struct s_tree_token	*child;
}	t_tree_token;

void	next_sym(t_token_list *list);
int		sym_accept(t_token_list *list, t_token_type type);
int		sym_expect(t_token_list *list, t_token_type type);
