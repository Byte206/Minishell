/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:46:19 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 19:51:15 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_cmd *cmd, t_env **env)
{
	int		i;
	char	*name;

	if (!cmd->argv[1])
		return (print_env_sorted(env));
	i = 1;
	while (cmd->argv[i])
	{
		name = get_name(cmd->argv[i]);
		if (!name)
		{
			if (handle_export_without_equal(cmd, env, i) != 0)
				return (1);
		}
		else
		{
			free(name);
			if (handle_export_with_equal(cmd, env, i) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}
