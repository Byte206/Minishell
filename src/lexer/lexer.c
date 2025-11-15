/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:45:22 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 18:55:23 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static void	set_joined_flag(t_token *new, t_token *tokens, int had_space)
{
	if (tokens == NULL || had_space)
		new->joined = 0;
	else
		new->joined = 1;
}

static int	process_token(t_token **tokens, char **ptr, char *prev_ptr)
{
	t_token	*new;
	int		had_space;

	skip_whitespace(ptr);
	if (!**ptr)
		return (0);
	had_space = (prev_ptr != *ptr);
	new = get_next_token(ptr);
	if (!new)
	{
		free_tokens(*tokens);
		*tokens = NULL;
		return (0);
	}
	set_joined_flag(new, *tokens, had_space);
	add_token_to_list(tokens, new);
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*tokens;
	char	*ptr;
	char	*prev_ptr;

	tokens = NULL;
	ptr = input;
	while (*ptr)
	{
		prev_ptr = ptr;
		if (!process_token(&tokens, &ptr, prev_ptr))
			return (tokens);
	}
	return (tokens);
}
