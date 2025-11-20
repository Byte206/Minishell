/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:57:53 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/20 14:58:36 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd, t_env **env)
{
	t_env	*cur;

	(void)cmd;
	if (!env || !*env)
		return (0);
	cur = *env;
	while (cur)
	{
		if (cur->name && cur->value)
			printf("%s=%s\n", cur->name, cur->value);
		cur = cur->next;
	}
	return (0);
}
