/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:37:44 by sunko             #+#    #+#             */
/*   Updated: 2023/10/30 10:58:13 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H

# include "../minishell.h"
# include "token.h"

# define INIT_SRC_POS	-1
# define ERRCHAR		0

char			next_char(t_source *src);
void			unget_char(t_source *src);
char			peek_char(t_source *src);
void			skip_white_space(t_source *src);
void			init_src(char *cmd, t_source *src);


#endif
