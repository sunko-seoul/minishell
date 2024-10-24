/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:29:15 by sunko             #+#    #+#             */
/*   Updated: 2023/11/26 08:28:54 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "minishell.h"

void	print_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
}

int	check_quote_error(char *line)
{
	if (ft_strchr(line, '\\'))
	{
		ft_putendl_fd("minishell: syntax error: backslash is not allowed", 2);
		return (1);
	}
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			line = ft_strchr(line + 1, *line);
			if (!line)
			{
				print_syntax_error(0);
				return (1);
			}
		}
		line++;
	}
	return (0);
}
