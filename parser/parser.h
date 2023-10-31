/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:24:19 by sunko             #+#    #+#             */
/*   Updated: 2023/10/31 12:15:35 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_word
{
	char	*word;
}	t_word;

typedef struct s_word_list
{
	t_word	*word_list;
}	t_word_list;

typedef struct s_assignment_word
{
	t_word	left;
	t_word	right;
}	t_assignment_word;

typedef struct s_redirect
{
	char	*type;  // Redirection type: ">", "<", ">>", "<<" etc.
	int		fd_name;
	t_word	*word;
}	t_redirect;

typedef struct s_redirect_list
{
	t_redirect				redirection;
	struct s_redirect_list	*next;
}	t_redirect_list;

typedef struct  s_simple_command_element
{
	union
	{
		t_word				word;
		t_assignment_word	assignment;
		t_redirect			redirection;
	}	u_element;
}	t_simple_command_element;

typedef struct s_simple_command
{
	t_simple_command_element	*element;
	size_t						num_elements;
}	t_simple_command;

typedef struct s_command
{
	union
	{
		t_simple_command	simple_command;
		t_redirect_list		redirect_list;
	}	u_command;
	int		is_simple;	// Indicates if it's a simple command or redirection list
}	t_command;

typedef struct s_pipeline
{
	t_command			command;
	struct s_pipeline	*next;
	int					is_pipeline;// Indicates if it's a pipeline
}	t_pipeline;

typedef struct s_m_list
{
	t_pipeline		pipeline;
	char			*logical_operator; // "&&" or "||" or NULL if not applicable
	struct s_m_list	*next;
}	t_m_list;

typedef struct s_subshell
{
	t_m_list	list;
}	t_subshell;

typedef struct s_syntax_tree
{
	t_m_list	list;
}	t_syntax_tree;
