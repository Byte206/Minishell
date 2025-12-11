/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 19:49:08 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_ast *ast, t_env **env, int exit_code)
{
	if (!ast->commands->cmd_name)
		return (0);
	if (ft_strncmp(ast->commands->cmd_name, "cd", 3) == 0)
		return (ft_cd(ast->commands, env));
	else if (ft_strncmp(ast->commands->cmd_name, "echo", 5) == 0)
		return (ft_echo(ast->commands->argv));
	else if (ft_strncmp(ast->commands->cmd_name, "env", 4) == 0)
		return (ft_env(ast->commands, env));
	else if (ft_strncmp(ast->commands->cmd_name, "exit", 5) == 0)
		return (ft_exit(ast, exit_code));
	else if (ft_strncmp(ast->commands->cmd_name, "export", 7) == 0)
		return (ft_export(ast->commands, env));
	else if (ft_strncmp(ast->commands->cmd_name, "pwd", 4) == 0)
		return (ft_pwd(ast->commands));
	else if (ft_strncmp(ast->commands->cmd_name, "unset", 6) == 0)
		return (ft_unset(ast->commands, env));
	return (0);
}

int	execution(t_ast *ast, t_env **env, int exit_code)
{
	if (!ast)
		return (1);
	set_signals();
	if (!ast->commands->next)
		exit_code = (exec_single_cmd(ast, env, exit_code));
	else
		exit_code = execute_multiple_commands(ast, env, exit_code);
	return (exit_code);
}
