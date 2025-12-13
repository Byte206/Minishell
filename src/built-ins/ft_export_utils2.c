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
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	new_node->prev = NULL;
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

void	free_export_vars(char *name, char *value)
{
	free(name);
	if (value)
		free(value);
}

int	handle_export_without_equal(t_cmd *cmd, t_env **env, int i)
{
	char	*name;
	char	*value;

	name = ft_strdup(cmd->argv[i]);
	if (!is_valid_identifier(name))
	{
		export_not_valid(cmd->argv[i]);
		free(name);
		return (1);
	}
	value = ft_strdup("");
	add_or_update_env(env, name, value);
	free_export_vars(name, value);
	return (0);
}
