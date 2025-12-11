/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:24:35 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 19:29:32 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_redir_in(t_redir *r)
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

static int	handle_redir_out(t_redir *r)
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

static int	handle_redir_append(t_redir *r)
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

static int	handle_heredoc(t_redir *r)
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

static char	*expand_heredoc_line(char *line, t_env *env, int exit_code)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		var_len;
	int		should_free;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			i++;
			var_name = get_var_name(&line[i], &var_len);
			if (var_name)
			{
				var_value = get_var_value(env, var_name, &should_free, exit_code);
				if (var_value)
				{
					j = 0;
					while (var_value[j])
						result = append_char_to_result(result, var_value[j++]);
					if (should_free)
						free(var_value);
				}
				free(var_name);
				i += var_len;
			}
			else
				result = append_char_to_result(result, '$');
		}
		else
		{
			result = append_char_to_result(result, line[i]);
			i++;
		}
	}
	return (result);
}

int	process_heredoc(t_redir *r, t_env *env, int exit_code)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, r->target, ft_strlen(r->target) + 1) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, env, exit_code);
		ft_putendl_fd(expanded, pipefd[1]);
		free(expanded);
		free(line);
	}
	close(pipefd[1]);
	r->heredoc_fd = pipefd[0];
	return (0);
}

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
