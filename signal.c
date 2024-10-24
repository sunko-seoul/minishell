/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunl <hyunjunl@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:36:05 by hyunjunl          #+#    #+#             */
/*   Updated: 2024/06/20 10:59:58 by hyunjunl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

volatile sig_atomic_t	g_last_signal_num;

static int	null_event(void)
{
	return (0);
}

static void	handle_signal(int signal_num)
{
	g_last_signal_num = signal_num;
	if (signal_num == SIGINT)
		rl_done = 1;
}

void	set_signal_handler(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = handle_signal;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, 0);
	sigaction(SIGQUIT, &act, 0);
	rl_catch_signals = 0;
	rl_event_hook = null_event;
}
