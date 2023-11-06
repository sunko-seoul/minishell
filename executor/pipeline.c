/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:59:26 by sunko             #+#    #+#             */
/*   Updated: 2023/11/06 16:13:44 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipeline(t_tree *tree)
{
	t_tree_token	*cur;
	int				cnt_pipeline;

	cnt_pipeline = 0;
	cur = tree->first_child;

	while (cur \
	&& !tree_check_type(cur, LOGICAL_END) \
	&& !tree_check_type(cur, LOGICAL_OR))
	{
		if (tree_check_type(cur, PIPE))
		{
			if (cur->child)
			{
				if (tree_check_type(cur->child, LOGICAL_END) \
				|| tree_check_type(cur->child, LOGICAL_OR) \
				|| tree_check_type(cur->child, PIPE))
					syntax_error(cur->child->type);
				else
					cnt_pipeline++;
			}
		}
		cur = cur->child;
	}
	return (cnt_pipeline);
}

void	create_main_child(t_tree *tree, t_pipe_info *info)
{
	pid_t	main_child_pid;
	int		pipe_cnt;
	int		i;
	int		state;

	pipe_cnt = count_pipelien(tree);
	main_child_pid = fork();
	i = -1;
	if (main_child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (main_child_pid == 0)
	{
		create_pipe(info);
		create_sub_child(info);
	}
	else
		waitpid(main_child_pid, &state, 0);
}

void	create_pipe(t_pipe_info *info)
{
	int		i;

	i = -1;
	info->pipe_fd = (int **)ft_malloc(sizeof(int *) * info->pipe_cnt);
	while (++i < info->pipe_cnt)
	{
		info->pipe_fd[i] = (int *)ft_malloc(sizeof(int) * 2);
		if (pipe(info->pipe_fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}


