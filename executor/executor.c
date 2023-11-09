/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:00:14 by sunko             #+#    #+#             */
/*   Updated: 2023/11/10 00:08:58 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	executor_value(t_tree_token *node, t_command *cmd)
{
	t_simple_command	*sim_cmd;
	int					i;

	if (!node || !node->u_value.value || !node->u_value.list)
		return ;
	if (node->is_list == 0)
	{
		if (node->type == CMD)
		{
			sim_cmd = create_simple_cmd();
			insert_simple_cmd(cmd, sim_cmd);
		}
		else if (node->type == SIM_CMD)
			insert_argument(cmd->simple_commands[cmd->idx], node->u_value.value);
		else if (node->type == REDIRECT)
		{
			if (node->tok_type == LEFT_REDIR || node->tok_type == LEFT_APPEND)
				cmd->simple_commands[cmd->idx]->inputfile = node->u_value.value;
			else if (node->tok_type == RIGHT_REDIR || node->tok_type == RIGHT_APPEND)
				cmd->simple_commands[cmd->idx]->outfile = node->u_value.value;
		}
	}
	if (node->is_list == 1)
		insert_list_argument(node, cmd);
}

void	insert_list_argument(t_tree_token *node, t_command *cmd)
{
	int		i;

	i = -1;
	while (node->u_value.list[++i])
		insert_argument(cmd->simple_commands[cmd->idx], node->u_value.list[i]);
}

void	executor_traversal(t_tree_token *node, t_command *cmd)
{
	executor_value(node, cmd);
	if (!node->left)
		executor_traversal(node->left, cmd);
	if (!node->right)
		executor_traversal(node->right, cmd);
}

void	executor(t_tree *tree, char *envp[])
{
	t_command			cmd;

	init_struct_cmd(&cmd);
	executor_traversal(tree->root, &cmd);
}

