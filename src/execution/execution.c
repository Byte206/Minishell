/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/01 13:51:15 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin(t_ast *ast, t_env **env, int exit_code)
{
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

static int	father(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	set_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	exec_external_cmd(t_ast *ast, t_env **env)
{
	int		pid;
	char	*path;

	set_execution_signals();
	pid = fork();
	if (pid == 0)
	{
		set_child_signals();
		if (ast->commands->redirections)
		{
			if (set_redirections(ast->commands->redirections) < 0)
				exit(1);
		}
		path = set_path(ast->commands->cmd_name, *env);
		if (!path)
		{
			printf("%s: command not found\n", ast->commands->cmd_name);
			exit(127);
		}
		execve(path, ast->commands->argv, env_to_char_array(*env));
		perror("execve");
		exit(127);
	}
	return (father(pid));
}

static int	exec_single_cmd(t_ast *ast, t_env **env, int exit_code)
{
	if (is_builtin(ast->commands->cmd_name))
		return (exec_builtin_cmd(ast, env, exit_code));
	return (exec_external_cmd(ast, env));
}

int	execution(t_ast *ast, t_env **env, int exit_code)
{
	if (!ast)
		return (1);
	set_signals();
	if (!ast->commands->next)
	{
		exit_code = (exec_single_cmd(ast, env, exit_code));
	}
	else
		exit_code = execute_multiple_commands(ast, env);
	return (exit_code);
}
