/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:41:09 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/20 14:26:19 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char *var)
{
	char	*sign;

	if (!var)
		return (NULL);
	sign = ft_strchr(var, '=');
	if (!sign)
		return (NULL);
	return (ft_substr(var, 0, sign - var));
}

char	*get_value(char *var)
{
	char	*sign;

	if (!var)
		return (NULL);
	sign = ft_strchr(var, '=');
	if (!sign)
		return (NULL);
	return (ft_strdup(sign + 1));
}

t_env	*build_node(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(value);
		free(name);
		return (NULL);
	}
	node->name = name;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
