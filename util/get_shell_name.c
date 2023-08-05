/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:32:45 by sunko             #+#    #+#             */
/*   Updated: 2023/07/28 23:04:13 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_shell_name(void)
{
	char	*shell;
	char	**split_shell_path;
	int		i;

	i = -1;
	shell = getenv("SHELL");
	split_shell_path = ft_split(shell, '/');
	while (split_shell_path[++i])
		;
	return (split_shell_path[--i]);
}
