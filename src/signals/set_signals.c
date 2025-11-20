/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:59:29 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 16:08:53 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	printf("\nminishell> ");
	return ;
}

void	handle_sigquit(int signum)
{
	(void)signum;
	return ;
}

void	set_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
