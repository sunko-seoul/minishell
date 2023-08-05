/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:43:42 by sunko             #+#    #+#             */
/*   Updated: 2023/07/28 22:44:12 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	call_signal(void)
{
	signal(SIGINT, sigint_ignore);
	signal(SIGQUIT, sigquit);
}

void	sigquit(int signum)
{
	(void)signum;
	exit(EXIT_SUCCESS);
}

void	sigint_ignore(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
