/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:49:27 by sunko             #+#    #+#             */
/*   Updated: 2023/10/29 14:50:02 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
