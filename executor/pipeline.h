/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:02:08 by sunko             #+#    #+#             */
/*   Updated: 2023/11/06 16:11:06 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

#include "../minishell.h"

typedef struct s_pipe_info
{
	int	**pipe_fd;
	int	pipe_cnt;
}	t_pipe_info;

#endif
