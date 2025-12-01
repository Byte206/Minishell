/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:34:59 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/01 13:38:25 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_child_process(t_cmd *cmd, int prev_read, int pipefd[2],
		t_env **env)
{
	int	pipe_write;

	set_child_signals();
	if (cmd->next)
	{
		close(pipefd[0]);
		pipe_write = pipefd[1];
	}
	else
		pipe_write = -1;
	child_execute(cmd, prev_read, pipe_write, env);
}

static int	setup_pipe(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next && pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

static int	fork_and_execute(t_cmd *cmd, int prev_read, int pipefd[2],
		t_env **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execute_child_process(cmd, prev_read, pipefd, env);
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

int	spawn_pipeline(t_ast *ast, t_env **env, int *pids)
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
		if (setup_pipe(cmd, pipefd))
			return (1);
		pids[i] = fork_and_execute(cmd, prev_read, pipefd, env);
		if (pids[i] < 0)
			return (1);
		handle_parent_pipes(&prev_read, pipefd, (cmd->next != NULL));
		cmd = cmd->next;
		i++;
	}
	if (prev_read != -1)
		close(prev_read);
	return (0);
}
