/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:55:48 by hyunjunl          #+#    #+#             */
/*   Updated: 2023/11/27 09:24:35 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "minishell.h"

static int	is_n_option(char *str)
{
	if (str == 0 || ft_strncmp(str, "-n", 2))
		return (0);
	str += 2;
	while (*str == 'n')
		++str;
	if (*str)
		return (0);
	return (1);
}

static int	write_args(char **argv, int nl)
{
	while (*argv)
	{
		if (ft_putstr_fd(*argv++, 1))
			return (1);
		if (*argv && ft_putchar_fd(' ', 1))
			return (1);
	}
	if (nl && ft_putchar_fd('\n', 1))
		return (1);
	return (0);
}

int	builtin_echo(t_cmd *cmd, t_sh_info *sh_info)
{
	char	**argv;
	int		nl;
	int		err;

	(void) sh_info;
	argv = cmd->argv + 1;
	nl = 1;
	while (is_n_option(*argv))
	{
		nl = 0;
		++argv;
	}
	err = write_args(argv, nl);
	if (err)
		perror("minishell: echo");
	return (err);
}
