/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:45:18 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 15:23:33 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespace(char **input)
{
	while (**input && (**input == ' ' || **input == '\t'))
		(*input)++;
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\0' || c == '|' || c == '<'
		|| c == '>');
}

void	print_tokens(t_token *tokens)
{
	t_token		*current;
	const char	*quotes[] = {"none", "single", "double"};

	current = tokens;
	while (current)
	{
		printf("Token: [%s] Type: %d Quote: %s Joined: %d\n",
			current->value, current->type,
			quotes[current->quote_type], current->joined);
		current = current->next;
	}
}
