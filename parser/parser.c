/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:32:04 by sunko             #+#    #+#             */
/*   Updated: 2023/11/07 16:49:09 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*parser(t_token_list *list, t_tree *tree)
{
	//printf("parser\n");
	tree->root->left = pipeline(list);
	tree->root->right = NULL;
	if (list->cur && (list->cur->type == LOGICAL_END || list->cur->type == LOGICAL_OR))
	{
		list->cur = list->cur->next;
		tree->root->right = pipeline(list);
	}
	return (tree);
}

t_tree_token	*pipeline(t_token_list *list)
{
	t_tree_token	*pipe_line;

	//printf("pipeline_call\n");
	if (!list->cur)
		return (NULL);
	pipe_line = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	pipe_line->left = command(list);
	pipe_line->right = NULL;
	if (list->cur && list->cur->type == PIPE)
	{
		list->cur = list->cur->next;
		pipe_line->right = pipeline(list);
	}
	//printf("pipeline_return\n");
	return pipe_line;
}

t_tree_token	*command(t_token_list *list)
{
	t_tree_token	*cmd;

	//printf("command_call\n");
	if (!list->cur)
		return (NULL);
	cmd = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	cmd->left = redirect_list(list);
	cmd->right = simple_cmd(list);
	if (!cmd->left)
		cmd->left = redirect_list(list);
	//printf("command_return\n");
	return (cmd);
}

t_tree_token	*redirect_list(t_token_list *list)
{
	t_tree_token	*redir_list;

	//printf("redirect_list call\n");
	if (!list->cur)
		return (NULL);
	redir_list = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	redir_list->left = redirect(list);
	if (redir_list->left == NULL)
		return (NULL);
	redir_list->right = redirect_list(list);
	//printf("redirect_list return\n");
	return (redir_list);
}

t_tree_token	*simple_cmd(t_token_list *list)
{
	t_tree_token	*simple_command;

	if (!list->cur)
		return (NULL);
	simple_command = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (is_cmd_type(list->cur, list->cur->type))
	{
		simple_command->left = create_value_token(cmd_file_path(list->cur->value));
		list->cur = list->cur->next;
		if (list->cur && is_cmd_type(list->cur, list->cur->type))
			simple_command->right = create_cmd_list_token(list, simple_command->left->u_value.value);
	}
	else
	{
		free(simple_command);
		return (NULL);
	}
	return (simple_command);
}

t_tree_token	*redirect(t_token_list *list)
{
	t_tree_token	*redir;

	//printf("redirect call\n");
	if (!list->cur)
		return (NULL);
	redir = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	if (is_redir_type(list->cur, list->cur->type))
	{
		redir->left = create_value_token(list->cur->value);
		list->cur = list->cur->next;
		if (list->cur->type == WORD)
		{
			redir->right = create_value_token(list->cur->value);
			list->cur = list->cur->next;
		}
		else
		{
			free(redir->left);
			free(redir);
			syntax_error(list->cur->type);
		}
	}
	else
	{
		free(redir);
		return (NULL);
	}
	//printf("redirect return\n");
	return (redir);
}

t_tree_token	*create_cmd_list_token(t_token_list *list, char *value)
{
	t_token			*tmp;
	char			**split_cmd;
	char			**new_list;
	int				i;
	int				j;

	split_cmd = ft_split(value, '/');
	i = -1;
	j = 0;
	while (split_cmd[++i])
		;
	tmp = list->cur;
	while (tmp && is_cmd_type(tmp, tmp->type))
	{
		j++;
		tmp = tmp->next;
	}
	new_list = (char **)ft_malloc(sizeof(char *) * (j + 2));
	j = 0;
	while (list->cur && is_cmd_type(list->cur, list->cur->type))
	{
		if (j == 0)
		{
			new_list[j] = split_cmd[--i];
			j++;
			continue;
		}
		else
			new_list[j] = list->cur->value;
		j++;
		list->cur = list->cur->next;
	}
	new_list[j] = 0;
	return (create_list_token(new_list));
}

t_tree_token	*create_value_token(char *value)
{
	t_tree_token	*new_token;

	new_token = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	new_token->is_list = 0;
	new_token->u_value.value = value;
	new_token->left = NULL;
	new_token->right = NULL;
	return (new_token);
}

t_tree_token	*create_list_token(char **list)
{
	t_tree_token	*new_token;

	new_token = (t_tree_token *)ft_malloc(sizeof(t_tree_token));
	new_token->is_list = 1;
	new_token->u_value.list = list;
	new_token->left = NULL;
	new_token->right = NULL;
	return (new_token);
}

int	is_redir_type(t_token *tok, t_token_type type)
{
	if (!tok)
		return (0);
	if (type == RIGHT_APPEND \
	|| type == LEFT_APPEND \
	|| type == RIGHT_REDIR \
	|| type == LEFT_REDIR)
		return (1);
	return (0);
}

int	is_cmd_type(t_token *tok, t_token_type type)
{
	if (!tok)
		return (0);
	if (type == WORD \
	|| type == SINGLE_QUOTE \
	|| type == DOUBLE_QUOTE)
		return (1);
	else
		return (0);
}

