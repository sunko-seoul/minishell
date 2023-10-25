/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 23:04:05 by sunko             #+#    #+#             */
/*   Updated: 2023/10/25 23:04:07 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include "source.h"

typedef struct s_token
{
	t_source	*src;	  /* source of input */
	int			text_len; /* length of token text */
	char		*text;	  /* token text */
}	t_token;

t_token	*tokenizer(t_source *src);
void	free_token(t_token *token);

#endif
