/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:00:14 by sunko             #+#    #+#             */
/*   Updated: 2023/11/11 21:25:38 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	executor_value(t_tree_token *node, t_command *cmd)
{
	t_simple_command	*sim_cmd;
	int					i;

	if (!node)
		return ;
	if (node->type == CMD)
	{
		sim_cmd = create_simple_cmd();
		insert_simple_cmd(cmd, sim_cmd);
		return ;
	}
	if (node->is_list == 0)
	{
		if (node->type == CMD_VALUE)
			insert_argument(cmd->simple_commands[cmd->idx], node->u_value.value);
		if (node->type == REDIRECT)
		{
			if (node->left->tok_type == LEFT_REDIR || node->left->tok_type == LEFT_APPEND)
				cmd->simple_commands[cmd->idx]->inputfile = node->right->u_value.value;
			else if (node->left->tok_type == RIGHT_REDIR || node->left->tok_type == RIGHT_APPEND)
				cmd->simple_commands[cmd->idx]->outfile = node->right->u_value.value;
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
	if (!node)
		return ;
	executor_value(node, cmd);
	if (node->left)
		executor_traversal(node->left, cmd);
	if (node->right)
		executor_traversal(node->right, cmd);
}

void	command_debug(t_tree *tree, t_command cmd)
{
	printf("\n========= command ==========\n");
	for (int i = 0; i < cmd.num_of_simple_cmd; ++i)
	{
		printf("%d simple command = ", i + 1);
		printf("(infile = %s), ", cmd.simple_commands[i]->inputfile);
		printf("(outfile = %s), ", cmd.simple_commands[i]->outfile);
		printf("(argument = ");
		for (int j = 0; j < cmd.simple_commands[i]->num_of_arg; ++j)
			printf("%s, ", cmd.simple_commands[i]->args[j]);
		printf(")\n");
	}
}

void	execute(t_command *cmd, char **envp)
{
	int		i;
	int		tmp_in;
	int		tmp_out;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	pid_t	pid;

	i = -1;
	while (++i < cmd->num_of_simple_cmd)
	{

	}
	waitpid(0, NULL, 0);
}

void	executor(t_tree *tree, char *envp[])
{
	t_command			cmd;

	init_struct_cmd(&cmd);
	executor_traversal(tree->root, &cmd);
	command_debug(tree, cmd);
	printf("\n================= execute ==================\n");
	create_fd_pipe(&cmd);
	set_io_fd(&cmd);
	execute(&cmd, envp);
}

