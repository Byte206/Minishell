/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:04:22 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 11:05:08 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_cmd *ast)
{
    if (ast->argv && ast->argv[1])
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        return ;
    }
	
}
