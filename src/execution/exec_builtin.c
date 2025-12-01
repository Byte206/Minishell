/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:45:37 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/01 13:46:35 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	save_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin < 0 || *saved_stdout < 0)
	{
		if (*saved_stdin >= 0)
			close(*saved_stdin);
		if (*saved_stdout >= 0)
			close(*saved_stdout);
		perror("dup");
		return (1);
	}
	return (0);
}

static void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	exec_builtin_cmd(t_ast *ast, t_env **env, int exit_code)
{
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_ret;

	if (save_fds(&saved_stdin, &saved_stdout))
		return (1);
	if (ast->commands->redirections)
	{
		if (set_redirections(ast->commands->redirections) < 0)
		{
			restore_fds(saved_stdin, saved_stdout);
			return (1);
		}
	}
	builtin_ret = exec_builtin(ast, env, exit_code);
	restore_fds(saved_stdin, saved_stdout);
	return (builtin_ret);
}
