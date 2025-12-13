/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:00:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/13 15:53:59 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_overflow(long long res, int sign, char digit, int *error)
{
	if (sign == 1 && res > (LLONG_MAX - (digit - '0')) / 10)
	{
		*error = 1;
		return (1);
	}
	if (sign == -1 && - res < (LLONG_MIN + (digit - '0')) / 10)
	{
		*error = 1;
		return (1);
	}
	return (0);
}

int	skip_whitespace_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}
