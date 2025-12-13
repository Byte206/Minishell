/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:30:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/13 15:30:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_heredoc_loop(t_redir *r, int pipefd,
				t_heredoc_ctx *ctx)
{
	char	*line;
	char	*expanded;
	int		len;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		len = ft_strlen(r->target);
		if (ft_strncmp(line, r->target, len) == 0 && line[len] == '\0')
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, ctx->env, ctx->exit_code);
		ft_putendl_fd(expanded, pipefd);
		free(expanded);
		free(line);
	}
	return (0);
}

int	process_heredoc(t_redir *r, t_env *env, int exit_code)
{
	int				pipefd[2];
	t_heredoc_ctx	ctx;

	ctx.env = env;
	ctx.exit_code = exit_code;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	process_heredoc_loop(r, pipefd[1], &ctx);
	close(pipefd[1]);
	r->heredoc_fd = pipefd[0];
	return (0);
}
