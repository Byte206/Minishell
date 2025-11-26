/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:57:03 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/25 19:57:06 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *look_for_exec_in_cwd(char *cmd_name)
{
    char   *cwd;
    char   *full_path;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (NULL);
    full_path = ft_strjoin(cwd, "/");
    full_path = ft_strjoin(full_path, cmd_name);
    free(cwd);
    if (access(full_path, X_OK) == 0)
        return (full_path);
    free(full_path);
    return (NULL);

}
