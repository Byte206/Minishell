/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:30:00 by bmonterd          #+#    #+#             */
/*   Updated: 2025/12/11 19:29:32 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_IN);
}

void	add_redir_to_cmd(t_cmd *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirections)
	{
		cmd->redirections = redir;
		return ;
	}
	current = cmd->redirections;
	while (current->next)
		current = current->next;
	current->next = redir;
}

char	*build_redir_target(t_token **tokens)
{
	char	*target;
	char	*tmp;

	if (!(*tokens) || !(*tokens)->value)
		return (NULL);
	target = ft_strdup((*tokens)->value);
	*tokens = (*tokens)->next;
	while (*tokens && (*tokens)->type == TOKEN_WORD && (*tokens)->joined)
	{
		tmp = ft_strjoin(target, (*tokens)->value);
		free(target);
		target = tmp;
		*tokens = (*tokens)->next;
	}
	return (target);
}
