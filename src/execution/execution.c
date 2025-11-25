/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/23 20:14:57 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_builtin(char *cmd_name)
{
	size_t	len;

	len = ft_strlen(cmd_name);
	if ((ft_strncmp(cmd_name, "cd", len) == 0 && len == 2)
		|| (ft_strncmp(cmd_name, "echo", len) == 0 && len == 4)
		|| (ft_strncmp(cmd_name, "env", len) == 0 && len == 3)
		|| (ft_strncmp(cmd_name, "exit", len) == 0 && len == 4)
		|| (ft_strncmp(cmd_name, "export", len) == 0 && len == 6)
		|| (ft_strncmp(cmd_name, "pwd", len) == 0 && len == 3)
		|| (ft_strncmp(cmd_name, "unset", len) == 0 && len == 5))
		return (1);
	return (0);
}

static int	exec_builtin(t_ast *ast, t_env **env)
{
	if (ft_strncmp(ast->commands->cmd_name, "cd", 3) == 0)
		return (ft_cd(ast->commands, env));
	else if (ft_strncmp(ast->commands->cmd_name, "echo", 5) == 0)
		return (ft_echo(ast->commands->argv));
	else if (ft_strncmp(ast->commands->cmd_name, "env", 4) == 0)
		return (ft_env(ast->commands, env));
	else if (ft_strncmp(ast->commands->cmd_name, "exit", 5) == 0)
		return (ft_exit(ast->commands));
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
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	exec_single_cmd(t_ast *ast, t_env **env)
{
	int		pid;
	char	*path;

	if (is_builtin(ast->commands->cmd_name))
		return (exec_builtin(ast, env));
	pid = fork();
	if (pid == 0)
	{
		// set_signals_child();
		// set_redirections(ast->commands->redirections);
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
	else
		return (father(pid));
}

int	execution(t_ast *ast, t_env **env)
{
	if (!ast)
		return (1);
	if (!ast->commands->next)
		return (exec_single_cmd(ast, env));
	// return (exec_with_pipe(ast, env));
	return (0);
}