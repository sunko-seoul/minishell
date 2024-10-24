/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_node_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 04:21:44 by sunko             #+#    #+#             */
/*   Updated: 2023/11/27 14:17:47 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "minishell.h"

int	collect_io_info(t_tree_node *io_redir_child, t_cmd *cmd, t_sh_info *sh_info)
{
	char	**word_lst;
	char	**target_file;

	word_lst = expand_word(sh_info, io_redir_child->sibling->value);
	target_file = 0;
	if (word_lst[0] == 0 || word_lst[1])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(io_redir_child->sibling->value, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		cmd->out_flag = ~0;
		free_str_arr(word_lst);
		return (1);
	}
	if (io_redir_child->type == TN_IN_REDIR
		|| io_redir_child->type == TN_HEREDOC)
		target_file = &cmd->in_file;
	else if (io_redir_child->type == TN_OUT_REDIR
		|| io_redir_child->type == TN_APPEND)
		target_file = &cmd->out_file;
	free(*target_file);
	*target_file = ft_strdup(word_lst[0]);
	free_str_arr(word_lst);
	return (0);
}

static int	get_argv_size(char **argv)
{
	int	idx;

	idx = 0;
	while (argv[idx])
		idx++;
	return (idx);
}

char	**join_argv(char **argv1, char **argv2)
{
	int		idx1;
	int		idx2;
	int		size;
	char	**ret;

	idx1 = 0;
	idx2 = 0;
	size = get_argv_size(argv1) + get_argv_size(argv2) + 1;
	ret = ft_calloc(size, sizeof(char *));
	while (argv1[idx1])
	{
		ret[idx1] = ft_strdup(argv1[idx1]);
		idx1++;
	}
	while (argv2[idx2])
	{
		ret[idx1 + idx2] = ft_strdup(argv2[idx2]);
		idx2++;
	}
	free_str_arr(argv1);
	free_str_arr(argv2);
	return (ret);
}

void	free_cmd_lst(t_cmd *cmd_lst)
{
	t_cmd	*cur_cmd;

	while (cmd_lst)
	{
		cur_cmd = cmd_lst;
		cmd_lst = cmd_lst->next;
		free_str_arr(cur_cmd->argv);
		free(cur_cmd->in_file);
		free(cur_cmd->out_file);
		free(cur_cmd);
	}
}
