/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:55:48 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:25:27 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "minishell.h"

int	builtin_pwd(t_cmd *cmd, t_sh_info *sh_info)
{
	(void) cmd;
	printf("%s\n", sh_info->pwd);
	return (0);
}
