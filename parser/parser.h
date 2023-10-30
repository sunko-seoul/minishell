/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:24:19 by sunko             #+#    #+#             */
/*   Updated: 2023/10/30 16:43:55 by sunko            ###   ########.fr       */
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
	char	*redirection; // input or output
	int		fd_num;
	t_word	word;
}	t_redirect;

typedef struct s_redirect_list
{
	t_redirect	*redirect_list;
}	t_redirect_list;

typedef struct  s_simple_command_element
{
	t_word				word;
	t_assignment_word	assignment;
	t_redirect			redirection;
}	t_simple_command_element;

typedef struct s_simple_command
{
	t_simple_command_element	*element;
}	t_simple_command;

typedef struct s_command
{
	t_simple_command	simple_command;
	t_subshell			subshell;
	t_redirect_list		redirect_list;
}	t_command;

typedef struct s_subshell
{
	t_list	list;
}	t_subshell;

typedef struct s_list
{
	char			*cur_list;
	char			*and_or;
	struct s_list	*next_list;
}	t_list;

typedef struct s_pipeline
{
	t_pipeline	pipeline;
	t_list		list;
	t_command	command;
}	t_pipeline;

typedef t_list	t_syntex_tree;
