/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:28:41 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 18:55:32 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_pipe_token(char **input)
{
	t_token	*token;

	token = new_token();
	token->value = ft_strdup("|");
	token->type = TOKEN_PIPE;
	(*input)++;
	return (token);
}

t_token	*create_redir_in_token(char **input)
{
	t_token	*token;

	token = new_token();
	(*input)++;
	if (**input == '<')
	{
		token->value = ft_strdup("<<");
		token->type = TOKEN_HEREDOC;
		(*input)++;
	}
	else
	{
		token->value = ft_strdup("<");
		token->type = TOKEN_REDIR_IN;
	}
	return (token);
}

t_token	*create_redir_out_token(char **input)
{
	t_token	*token;

	token = new_token();
	(*input)++;
	if (**input == '>')
	{
		token->value = ft_strdup(">>");
		token->type = TOKEN_APPEND;
		(*input)++;
	}
	else
	{
		token->value = ft_strdup(">");
		token->type = TOKEN_REDIR_OUT;
	}
	return (token);
}

t_token	*get_next_token(char **input)
{
	if (!**input)
		return (NULL);
	if (**input == '|')
		return (create_pipe_token(input));
	if (**input == '<')
		return (create_redir_in_token(input));
	if (**input == '>')
		return (create_redir_out_token(input));
	if (**input == '\'')
		return (create_quoted_token(input, '\''));
	if (**input == '"')
		return (create_quoted_token(input, '"'));
	return (create_word_token(input));
}
