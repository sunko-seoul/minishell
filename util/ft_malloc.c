/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:49:27 by sunko             #+#    #+#             */
/*   Updated: 2023/10/30 10:29:11 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	*ft_malloc(size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
	{
		perror("malloc : ");
		exit(EXIT_FAILURE);
	}
	return new_ptr;
}
