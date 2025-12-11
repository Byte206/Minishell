/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:00:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redir_in(t_redir *r)
{
	int	fd;

	if (!r->target)
		return (-1);
	fd = open(r->target, O_RDONLY);
	if (fd < 0)
	{
		perror(r->target);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_redir_out(t_redir *r)
{
	int	fd;

	if (!r->target)
		return (-1);
	fd = open(r->target, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror(r->target);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redir_append(t_redir *r)
{
	int	fd;

	if (!r->target)
		return (-1);
	fd = open(r->target, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror(r->target);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_heredoc(t_redir *r)
{
	int	fd_dup;

	if (r->heredoc_fd == -1)
		return (-1);
	fd_dup = dup(r->heredoc_fd);
	if (fd_dup == -1)
	{
		perror("dup");
		return (-1);
	}
	dup2(fd_dup, STDIN_FILENO);
	close(fd_dup);
	return (0);
}

void	close_heredoc_fds(t_ast *ast)
{
	t_cmd	*cmd;
	t_redir	*redir;

	if (!ast)
		return ;
	cmd = ast->commands;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd != -1)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
