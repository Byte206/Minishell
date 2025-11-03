/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:27:38 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/03 13:42:42 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"





t_env *set_actual_env(char *var)
{
	char  *name;
	char  *value;
	t_env *new;

	name = get_name(var);
	value = get_value(var);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (NULL);
	}
	new = create_node(name, value);
	free(name);
	free(value);
	return (new);
}

t_env *init_env(char **envp)
{
	t_end *head;
	t_end *new;
	int	  i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new = set_actual_env(envp[i]);
		if (new)
			add_node(&head, new);
		i++;
	}
	return (head);
}
