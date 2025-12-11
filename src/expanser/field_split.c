/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 00:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	normalize_tabs(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\t')
			s[i] = ' ';
		i++;
	}
}

static void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static void	create_new_token(t_token **after, char *value)
{
	t_token	*newtok;

	newtok = new_token();
	if (newtok)
	{
		newtok->value = ft_strdup(value);
		newtok->type = TOKEN_WORD;
		newtok->quote_type = QUOTE_NONE;
		newtok->joined = 0;
		newtok->next = (*after)->next;
		(*after)->next = newtok;
		*after = newtok;
	}
}

static void	insert_remaining_parts(t_token *after, char **parts)
{
	int	j;

	j = 1;
	while (parts[j])
	{
		if (parts[j][0] != '\0')
			create_new_token(&after, parts[j]);
		j++;
	}
}

static void	handle_split_parts(t_token *current, char *expanded, char **parts)
{
	t_token	*insert_after;

	(void)expanded;
	insert_after = current;
	free(current->value);
	current->value = ft_strdup(parts[0]);
	current->joined = 0;
	insert_remaining_parts(insert_after, parts);
}

void	apply_field_splitting(t_token *current, char *expanded)
{
	char	**parts;

	normalize_tabs(expanded);
	parts = ft_split(expanded, ' ');
	if (parts && parts[0] && parts[1])
		handle_split_parts(current, expanded, parts);
	else
	{
		free(current->value);
		current->value = expanded;
		expanded = NULL;
	}
	free_parts(parts);
	if (expanded)
		free(expanded);
}
