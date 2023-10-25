/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:27:55 by sunko             #+#    #+#             */
/*   Updated: 2023/10/25 23:18:16 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_cmd(void)
{
	char	*buf;
	int		cmd_len;
	int		buf_len;
	char	*command;
	char	*cmd_buf;

	command = NULL;
	cmd_len = 0;
	while (1)
	{
		buf = readline(NULL);
		if (!buf)
			return NULL;
		if (buf[0] == 0)
			continue;
		buf_len = ft_strlen(buf);
		if (!command)
			command = malloc(buf_len + 1);
		else
		{
			cmd_buf = ft_realloc(command, buf_len + cmd_len + 1);
			if (cmd_buf)
			{
				command = cmd_buf;
			}
			else
			{
				free(command);
				command = NULL;
			}
		}
		if (!command)
		{
			write(2, "error\n", 7);
			return NULL;
		}
		ft_strlcpy(command + cmd_len, buf, cmd_len + buf_len + 1);
		if (buf_len == 1 || buf[buf_len - 1] != '\\')
			return command;
		command[cmd_len + buf_len - 1] = '\0';
		buf_len -= 1;
		write(1, "> ", 2);
		cmd_len += buf_len;
	}
	return command;
}
