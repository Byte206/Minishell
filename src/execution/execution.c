/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/20 14:57:03 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0 ||
		ft_strcmp(cmd_name, "echo") == 0 ||
		ft_strcmp(cmd_name, "env") == 0 ||
		ft_strcmp(cmd_name, "exit") == 0 ||
		ft_strcmp(cmd_name, "export") == 0 ||
		ft_strcmp(cmd_name, "pwd") == 0 ||
		ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	return (0);
}
static int execute_builtin(t_ast *ast, t_env **env)
{
	if (ft_strcmp(ast->commands->cmd_name, "cd") == 0)
		return (ft_cd(ast->commands, env));
	else if (ft_strcmp(ast->commands->cmd_name, "echo") == 0)
		return (ft_echo(ast->commands));
	else if (ft_strcmp(ast->commands->cmd_name, "env") == 0)
		return (ft_env(ast->commands, env));
	else if (ft_strcmp(ast->commands->cmd_name, "exit") == 0)
		return (ft_exit(ast->commands));
	else if (ft_strcmp(ast->commands->cmd_name, "export") == 0)
		return (ft_export(ast->commands, env));
	else if (ft_strcmp(ast->commands->cmd_name, "pwd") == 0)
		return (ft_pwd(ast->commands));
	else if (ft_strcmp(ast->commands->cmd_name, "unset") == 0)
		return (ft_unset(ast->commands, env));
}

int	execution(t_ast *ast, t_env **env)
{
	if (!ast)
		return (1);
	if (ast->commands->cmd_name)
	{
		if (is_builtin(ast->commands->cmd_name))
			return (execute_builtin(ast, env));
		else
			return (execute_external(ast, env));
	}
	return (0);
}