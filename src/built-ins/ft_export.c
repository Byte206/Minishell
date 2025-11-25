/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:46:19 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/24 11:46:20 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_not_valid(char *name)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	is_valid_identifier(char *name)
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

int	ft_export(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*name;
	char	*value;

	if (!cmd->argv[1])
		return (print_env_sorted(env));
	i = 1;
	while (cmd->argv[i])
	{
		name = get_name(cmd->argv[i]);
		value = get_value(cmd->argv[i]);
		if (!is_valid_identifier(name))
		{
			export_not_valid(name);
			free(name);
			free(value);
			return (1);
		}
		value = ft_strchr(cmd->argv[i], '=') ? value : ft_strdup("");
		add_or_update_env(env, name, value);
		free(name);
		free(value);
		i++;
	}
	return (0);
}
