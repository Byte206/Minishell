/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 12:37:44 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 12:38:49 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_env(t_cmd	*ast)
{
	if (ast->argv && ast->argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return ;
	}
	else
	{
	}
		
}
