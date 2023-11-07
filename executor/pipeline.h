/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:02:08 by sunko             #+#    #+#             */
/*   Updated: 2023/11/06 18:14:47 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

#include "../minishell.h"

typedef struct s_cmd_info
{
	int		in_fd;
	int		out_fd;
	int		**pipe_fd;
	int		sub_child_idx;
	int		pipe_cnt;
	char	*cmd;
	char	**cmd_arg;
}	t_cmd_info;

#endif
