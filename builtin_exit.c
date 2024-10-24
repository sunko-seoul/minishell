/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 07:28:23 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:24:59 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	builtin_exit(t_cmd *cmd, t_sh_info *sh_info)
{
	char		**argv;
	long long	n;
	int			err;

	argv = cmd->argv + 1;
	printf("exit\n");
	if (*argv == 0)
		exit(sh_info->exit);
	err = 0;
	n = ft_atoll(*argv, &err);
	if (err)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	if (*(argv + 1))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit(n);
}
