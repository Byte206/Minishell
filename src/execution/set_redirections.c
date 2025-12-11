/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:24:35 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 19:49:08 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_redirections(t_redir *redirections)
{
	while (redirections)
	{
		if (redirections->type == REDIR_IN)
		{
			if (handle_redir_in(redirections) < 0)
				return (-1);
		}
		else if (redirections->type == REDIR_OUT)
		{
			if (handle_redir_out(redirections) < 0)
				return (-1);
		}
		else if (redirections->type == REDIR_APPEND)
		{
			if (handle_redir_append(redirections) < 0)
				return (-1);
		}
		else if (redirections->type == REDIR_HEREDOC)
		{
			if (handle_heredoc(redirections) < 0)
				return (-1);
		}
		redirections = redirections->next;
	}
	return (0);
}

int	process_all_heredocs(t_ast *ast, t_env *env, int exit_code)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = ast->commands;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (process_heredoc(redir, env, exit_code) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
