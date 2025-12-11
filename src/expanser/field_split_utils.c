/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:00:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	normalize_tabs(char *s)
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

void	free_parts(char **parts)
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

void	create_new_token(t_token **after, char *value)
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

void	insert_remaining_parts(t_token *after, char **parts)
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
