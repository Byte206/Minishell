/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:28:15 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 16:00:01 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	validate_pipe_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
		return (syntax_error("|"));
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
				return (syntax_error("|"));
		}
		current = current->next;
	}
	return (1);
}

static int	validate_redir_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_redir_token(current->type))
		{
			if (!current->next)
				return (syntax_error(NULL));
			if (current->next->type != TOKEN_WORD)
				return (syntax_error(current->next->value));
		}
		current = current->next;
	}
	return (1);
}

static int	validate_invalid_ops(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value)
		{
			if (ft_strchr(current->value, '&'))
				return (syntax_error("&"));
			if (ft_strncmp(current->value, "<<<", 3) == 0)
				return (syntax_error("<<<"));
		}
		current = current->next;
	}
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (!validate_pipe_syntax(tokens))
		return (0);
	if (!validate_redir_syntax(tokens))
		return (0);
	if (!validate_invalid_ops(tokens))
		return (0);
	return (1);
}
