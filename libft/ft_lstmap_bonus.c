/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjoo <hyunjoo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 04:52:00 by hyunjoo           #+#    #+#             */
/*   Updated: 2023/03/14 05:19:45 by hyunjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static t_list	*lstnew(void *lst_con, void *(*f)(void *))
{
	t_list	*temp;

	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
		return (0);
	temp->content = f(lst_con);
	if (!(temp->content))
	{
		free(temp);
		return (0);
	}
	temp->next = 0;
	return (temp);
}

static void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static void	lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst)
	{
		temp = *lst;
		*lst = temp->next;
		del(temp->content);
		free(temp);
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*head;

	head = 0;
	while (lst)
	{
		temp = lstnew(lst->content, f);
		if (!temp)
		{
			lstclear(&head, del);
			return (0);
		}
		lstadd_back(&head, temp);
		lst = lst->next;
	}
	return (head);
}
