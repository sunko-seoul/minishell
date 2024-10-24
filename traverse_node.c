/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 04:22:00 by sunko             #+#    #+#             */
/*   Updated: 2023/11/27 14:18:03 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	traverse_io_redir(t_tree_node *tn_io_redir, t_cmd *cmd,
														t_sh_info *sh_info)
{
	int	fd;

	if (collect_io_info(tn_io_redir->child, cmd, sh_info))
		return (1);
	if (tn_io_redir->child->type == TN_IN_REDIR
		|| tn_io_redir->child->type == TN_HEREDOC)
		fd = open_file(cmd->in_file, O_RDONLY, 1);
	else
	{
		if (tn_io_redir->child->type == TN_OUT_REDIR)
			cmd->out_flag = O_WRONLY | O_CREAT | O_TRUNC;
		else if (tn_io_redir->child->type == TN_APPEND)
			cmd->out_flag = O_WRONLY | O_CREAT | O_APPEND;
		fd = open_file(cmd->out_file, cmd->out_flag, 1);
	}
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

static void	traverse_cmd_elem_node(t_tree_node *tn_cmd_elem, t_cmd *cmd,
														t_sh_info *sh_info)
{
	t_tree_node	*cur_sibling;

	cur_sibling = tn_cmd_elem;
	while (cur_sibling)
	{
		if (cur_sibling->child->type == TN_WORD)
			cmd->argv = join_argv(cmd->argv, \
							expand_word(sh_info, cur_sibling->child->value));
		else if (cur_sibling->child->type == TN_IO_REDIR)
			if (traverse_io_redir(cur_sibling->child, cmd, sh_info))
				return ;
		cur_sibling = cur_sibling->sibling;
	}
}

static void	traverse_cmd_node(t_tree_node *tn_cmd, t_cmd *cmd_lst,
														t_sh_info *sh_info)
{
	t_cmd		*cur_cmd;
	t_tree_node	*cur_sibling;

	traverse_cmd_elem_node(tn_cmd->child, cmd_lst, sh_info);
	cur_sibling = tn_cmd->sibling;
	cur_cmd = cmd_lst;
	while (cur_sibling)
	{
		cur_cmd->next = ft_calloc(1, sizeof(t_cmd));
		cur_cmd->next->argv = ft_calloc(1, sizeof(char *));
		traverse_cmd_elem_node(cur_sibling->child, cur_cmd->next, sh_info);
		cur_sibling = cur_sibling->sibling;
		cur_cmd = cur_cmd->next;
	}
}

static void	traverse_expr_node(t_tree_node *tn_expr, t_sh_info *sh_info)
{
	t_cmd	*cmd_lst;

	if (tn_expr->child->type == TN_LIST)
		traverse_node(tn_expr->child, sh_info);
	else
	{
		cmd_lst = ft_calloc(1, sizeof(t_cmd));
		cmd_lst->argv = ft_calloc(1, sizeof(char *));
		traverse_cmd_node(tn_expr->child, cmd_lst, sh_info);
		execute_cmds(cmd_lst, sh_info);
		free_cmd_lst(cmd_lst);
	}
	if (!tn_expr->sibling)
		return ;
	if ((tn_expr->sibling->type == TN_LOGICAL_AND && sh_info->exit == 0)
		|| (tn_expr->sibling->type == TN_LOGICAL_OR && sh_info->exit != 0))
		traverse_node(tn_expr->sibling->sibling, sh_info);
}

void	traverse_node(t_tree_node *tree_node, t_sh_info *sh_info)
{
	if (tree_node->type == TN_LIST)
		traverse_expr_node(tree_node->child, sh_info);
	else if (tree_node->type == TN_EXPR)
		traverse_expr_node(tree_node, sh_info);
}
