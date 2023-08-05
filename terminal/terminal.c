/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:38:16 by sunko             #+#    #+#             */
/*   Updated: 2023/08/05 14:41:21 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	disable_ctrl_c_output(t_termios *origin_attr)
{
	int			val;
	t_termios	*new_attr;

	val = tcgetattr(STDIN_FILENO, origin_attr);
	if (val == -1)
		print_error();
	new_attr = origin_attr;
	new_attr->c_lflag &= ~ECHOCTL;
	val = tcsetattr(STDIN_FILENO, TCSANOW, new_attr);
	if (val == -1)
		print_error();
}
