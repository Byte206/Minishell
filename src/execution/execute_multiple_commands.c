/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:14:08 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/30 09:00:13 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_cmds(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

static void	exec_external_child(t_cmd *cmd, t_env **env)
{
	char	*path;

	path = set_path(cmd->cmd_name, *env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->cmd_name);
		exit(127);
	}
	execve(path, cmd->argv, env_to_char_array(*env));
	perror("execve");
	exit(127);
}

static void	exec_child_builtin(t_cmd *cmd, t_env **env)
{
	t_ast	tmp;

	if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
		exit(ft_cd(cmd, env));
	if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		exit(ft_echo(cmd->argv));
	if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		exit(ft_env(cmd, env));
	if (ft_strncmp(cmd->cmd_name, "exit", 5) == 0)
	{
		tmp.commands = cmd;
		ft_exit(&tmp, 0);
		exit(0);
	}
	if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		exit(ft_export(cmd, env));
	if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		exit(ft_pwd(cmd));
	if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		exit(ft_unset(cmd, env));
}

static void	child_execute(t_cmd *cmd, int prev_read, int pipe_write, t_env **env)
{
	if (prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (pipe_write != -1)
	{
		dup2(pipe_write, STDOUT_FILENO);
		close(pipe_write);
	}
	if (set_redirections(cmd->redirections) < 0)
		exit(1);
	exec_child_builtin(cmd, env);
	exec_external_child(cmd, env);
}

static int	wait_children(int *pids, int n)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static void	handle_parent_pipes(int *prev_read, int pipefd[2], int has_next)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (has_next)
	{
		close(pipefd[1]);
		*prev_read = pipefd[0];
	}
	else
		*prev_read = -1;
}

static int	spawn_pipeline(t_ast *ast, t_env **env, int *pids)
{
	t_cmd	*cmd;
	int		prev_read;
	int		pipefd[2];
	int		i;

	prev_read = -1;
	cmd = ast->commands;
	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (cmd->next)
				close(pipefd[0]);
			child_execute(cmd, prev_read, (cmd->next) ? pipefd[1] : -1, env);
		}
		if (pids[i] < 0)
			return (perror("fork"), 1);
		handle_parent_pipes(&prev_read, pipefd, (cmd->next != NULL));
		cmd = cmd->next;
		i++;
	}
	if (prev_read != -1)
		close(prev_read);
	return (0);
}

int	execute_multiple_commands(t_ast *ast, t_env **env)
{
	int	cmds_count;
	int	*pids;
	int	status;

	if (!ast || !ast->commands)
		return (1);
	cmds_count = count_cmds(ast->commands);
	pids = malloc(sizeof(int) * cmds_count);
	if (!pids)
		return (1);
	if (spawn_pipeline(ast, env, pids) != 0)
	{
		free(pids);
		return (1);
	}
	status = wait_children(pids, cmds_count);
	free(pids);
	return (status);
}
