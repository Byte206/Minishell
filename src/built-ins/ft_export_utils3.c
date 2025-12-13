/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:35:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/13 15:35:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_export_vars(char *name, char *value)
{
	free(name);
	if (value)
		free(value);
}

int	handle_export_with_equal(t_cmd *cmd, t_env **env, int i)
{
	char	*name;
	char	*value;

	name = get_name(cmd->argv[i]);
	value = get_value(cmd->argv[i]);
	if (!is_valid_identifier(name))
	{
		export_not_valid(cmd->argv[i]);
		free_export_vars(name, value);
		return (1);
	}
	if (!value && ft_strchr(cmd->argv[i], '='))
		value = ft_strdup("");
	if (value)
		add_or_update_env(env, name, value);
	free_export_vars(name, value);
	return (0);
}
