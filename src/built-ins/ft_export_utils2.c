/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:00:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*create_env_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_or_update_env(t_env **env, char *name, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
		{
			free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return ;
		}
		current = current->next;
	}
	new_node = create_env_node(name, value);
	new_node->next = *env;
	if (*env)
		(*env)->prev = new_node;
	*env = new_node;
}

void	export_not_valid(char *name)
{
	ft_putstr_fd("export: `", 2);
	if (name)
		ft_putstr_fd(name, 2);
	else
		ft_putstr_fd("", 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	is_valid_identifier(char *name)
{
	int	i;

	if (!name || !name[0] || (name[0] >= '0' && name[0] <= '9'))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A'
					&& name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9')
				|| (name[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

int	handle_export_without_equal(t_cmd *cmd, t_env **env, int i)
{
	char	*name;

	name = ft_strdup(cmd->argv[i]);
	if (!is_valid_identifier(name))
	{
		export_not_valid(cmd->argv[i]);
		free(name);
		return (1);
	}
	add_or_update_env(env, name, NULL);
	free(name);
	return (0);
}
