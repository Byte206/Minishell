/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:45:53 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/24 11:45:57 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_node(t_env **env, t_env *node_to_delete)
{
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	else
		*env = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	free(node_to_delete->name);
	free(node_to_delete->value);
	free(node_to_delete);
}

int	ft_unset(t_cmd *cmd, t_env **env)
{
	if (!cmd->argv[1])
		return (0);
	while (*env)
	{
		if (ft_strncmp(cmd->argv[1], (*env)->name, ft_strlen(cmd->argv[1])
				+ 1) == 0)
		{
			delete_node(env, *env);
			return (0);
		}
		env = &(*env)->next;
	}
	printf("variable: %s: doesn't exist\n", cmd->argv[1]);
	return (0);
}
