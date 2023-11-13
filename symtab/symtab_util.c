/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:57:30 by sunko             #+#    #+#             */
/*   Updated: 2023/11/13 23:00:11 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtab.h"

void	free_symtab(t_symtab *symtab)
{
	t_symtab_entry	*entry;
	t_symtab_entry	*next;

	if (!symtab)
		return ;
	entry = symtab->first;
	while (entry)
	{
		if (entry->name)
			free(entry->name);
		if (entry->val)
			free(entry->val);
		next = entry->next;
		free(entry);
		entry = next;
	}
	free(symtab);
}
