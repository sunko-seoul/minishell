/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:09:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/07 16:49:57 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parser(t_token_list *list, t_tree *tree);
int		check_next_type(t_token_list *token_list, t_token_type type);
int		check_cur_type(t_token_list *token_list, t_token_type type);
char	*type_to_string(t_token_type type);
void	syntax_error(t_token_type type);


int main(int argc , char *argv[], char *envp[])
{
	char		*command;
	t_termios	origin_attr;
	t_source	src;
	(void)argc;
	(void)argv;

	if (argc != 1)
		arg_error();
	disable_ctrl_c_output(&origin_attr);
	call_signal();
	while (1)
	{
		command = readline("minishell > ");
		if (!command)
			exit(EXIT_SUCCESS);
		else if (command[0] == 0)
		{
			free(command);
			continue;
		}
		else if (ft_strncmp("exit", command, 5) == 0)
		{
			free(command);
			break;
		}
		init_src(command, &src);
		parse_execute(&src, envp);
		add_history(command);
	}
	exit(EXIT_SUCCESS);
}

int	parse_execute(t_source *src, char *envp[])
{
	t_token_list	*token_list;
	t_tree			*tree;
	pid_t			pid;
	t_cmd_info		info;
	int				status;

	ft_memset(&info, 0, sizeof(t_cmd_info));
	skip_white_space(src);
	token_list = create_token_list();
	token_list = tokenizer(token_list, src);
	/* token debug */
	token_debug(token_list);

	tree = (t_tree *)ft_malloc(sizeof(t_tree));
	tree->root = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	tree->root->left = NULL;
	tree->root->right = NULL;
	tree = parser(token_list, tree);
	/* tree debug */
	tree_debug(tree);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		pipe_child(tree);
		executor(tree, envp);
	}
	else
		waitpid(0, &status, 0);
	return 0;
}


int	check_next_type(t_token_list *token_list, t_token_type type)
{
	if (!token_list->cur)
		return (-1);
	if (token_list->cur == token_list->tail)
		return (-1);
	if (token_list->cur->next->type == type)
		return (1);
	else
		return (0);
}

int	check_cur_type(t_token_list *token_list, t_token_type type)
{
	if (!token_list->cur)
		return (0);
	if (token_list->cur->type == type)
		return (1);
	else
		return (0);
}

char	*type_to_string(t_token_type type)
{
	if (type == LOGICAL_END)
		return "&&";
	else if (type == LOGICAL_OR)
		return "||";
	else if (type == WILDCARD)
		return "*";
	else if (type == SINGLE_QUOTE)
		return "'";
	else if (type == DOUBLE_QUOTE)
		return "\"";
	else if (type == PIPE)
		return "|";
	else if (type == LEFT_PAREN)
		return "(";
	else if (type == RIGHT_PAREN)
		return ")";
	else if (type == RIGHT_REDIR)
		return ">";
	else if (type == LEFT_REDIR)
		return "<";
	else if (type == RIGHT_APPEND)
		return ">>";
	else if (type == LEFT_APPEND)
		return "<<";
	else if (type == DOLLAR_SIGN)
		return "$";
	return NULL;
}

void	syntax_error(t_token_type type)
{
	char	*err;

	err = type_to_string(type);
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, err, ft_strlen(err));
	write(2, "\'\n", 2);
	exit(EXIT_FAILURE);
}

