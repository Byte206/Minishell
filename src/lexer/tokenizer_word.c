/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:30:00 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 21:52:40 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quoted_len(char **input, char quote_char)
{
	int	len;

	len = 0;
	while (**input && **input != quote_char)
	{
		len++;
		(*input)++;
	}
	return (len);
}

static void	set_quote_type(t_token *token, char quote_char)
{
	if (quote_char == '\'')
		token->quote_type = QUOTE_SINGLE;
	else
		token->quote_type = QUOTE_DOUBLE;
}

t_token	*create_quoted_token(char **input, char quote_char)
{
	t_token	*token;
	char	*start;
	int		len;

	(*input)++;
	start = *input;
	len = get_quoted_len(input, quote_char);
	if (**input != quote_char)
	{
		print_error("unclosed quote");
		return (NULL);
	}
	token = new_token();
	token->value = ft_substr(start, 0, len);
	token->type = TOKEN_WORD;
	set_quote_type(token, quote_char);
	(*input)++;
	return (token);
}

t_token	*create_word_token(char **input)
{
	char	*start;
	int		len;
	t_token	*token;

	start = *input;
	len = 0;
	while (**input && !is_separator(**input))
	{
		if (**input == '\'' || **input == '"')
			break ;
		len++;
		(*input)++;
	}
	token = new_token();
	token->value = ft_substr(start, 0, len);
	token->type = TOKEN_WORD;
	token->quote_type = QUOTE_NONE;
	return (token);
}
