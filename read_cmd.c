/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:27:55 by sunko             #+#    #+#             */
/*   Updated: 2023/10/21 18:31:48 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;
	size_t	old_size;

	old_size = ft_strlen((char *)ptr);
	if (ptr == NULL)
		return malloc(new_size);
	else if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}
	else
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
			return NULL;
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
		return new_ptr;
	}
}

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
		write(1, ">", 1);
		cmd_len += buf_len;
	}
	return command;
}
