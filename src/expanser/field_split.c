/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
