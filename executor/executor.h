/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:59:25 by sunko             #+#    #+#             */
/*   Updated: 2023/11/07 11:17:56 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

char	*join_binpath_cmd(char *path[], char *cmd);
char	*cmd_file_path(char *cmd);
void	executor(t_tree *tree, char *envp[]);

#endif
