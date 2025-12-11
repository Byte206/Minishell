/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:00:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	father(int pid)
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

int	exec_external_cmd(t_ast *ast, t_env **env)
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

int	handle_redir_only_cmd(t_ast *ast)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (set_redirections(ast->commands->redirections) < 0)
			exit(1);
		exit(0);
	}
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_single_cmd(t_ast *ast, t_env **env, int exit_code)
{
	if (process_all_heredocs(ast, *env, exit_code) < 0)
		return (1);
	if (!ast->commands->cmd_name || !*ast->commands->cmd_name)
	{
		if (ast->commands->redirections)
			return (handle_redir_only_cmd(ast));
		return (0);
	}
	if (is_builtin(ast->commands->cmd_name))
		return (exec_builtin_cmd(ast, env, exit_code));
	return (exec_external_cmd(ast, env));
}
