/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:37:34 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 10:40:49 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void call_export(char *name, char *value, t_env **env)
{
    char *var;
    t_cmd *cmd;

    cmd->argv = malloc(sizeof(char *) * 2);
    var = ft_strjoin(name, "=");
    var = ft_strjoin(var, value);
    cmd->argv[0] = var;
    cmd->argv[1] = NULL;
    cmd->cmd_name = "export";
    cmd->redirections = NULL;
    cmd->next = NULL;
    ft_export(cmd, env);
    free(var);
    free(cmd->argv);
    free(cmd);
    return (0)
}

int		ft_cd(t_cmd *cmd, t_env **env)
{
    char    *new_path;
    char    *old_path;

    old_path = getcwd(NULL, 0);
    if (chdir(cmd->argv[1]) != 0)
    {
        perror("cd");
        free(old_path);
        return (1);
    }
    new_path = getcwd(NULL, 0);
    // Update PWD and OLDPWD in the environment list
    call_export("OLDPWD", old_path, env);
    call_export("PWD", new_path, env);
    free(old_path);
    free(new_path);
    return (0);
}
