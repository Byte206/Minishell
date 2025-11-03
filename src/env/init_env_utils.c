/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:41:09 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/03 13:41:32 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char  *get_name(char *var)
{
	char  *sign;
	char  *name;

	sign = ft_strchr(var, '=');
	if (sign)
		return (NULL);
	name = ft_substr(var, 0, sign - var);
	return (name);
}

char  *get_value(char *var)
{
	char  *sign;
	char  *value;

	sign = ft_strchr(var, '=');
	if (!sign)
		return (NULL);
	value = ft_strdup(igual + 1);
	return (value);
}
