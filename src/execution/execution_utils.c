/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:29:05 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/01 13:46:25 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd_name)
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

int	count_cmds(t_cmd *cmd)
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

int	wait_children(int *pids, int n)
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

void	handle_parent_pipes(int *prev_read, int pipefd[2], int has_next)
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
