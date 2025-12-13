/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byte <byte@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:57:03 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/30 13:32:30 by byte             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*look_for_exec_in_cwd(char *cmd_name)
{
	char	*cwd;
	char	*temp;
	char	*full_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	temp = ft_strjoin(cwd, "/"); // Guarda en temp
	free(cwd);                   // Libera cwd
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd_name);
	free(temp); // ← LIBERA temp aquí
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
