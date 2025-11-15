/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:18:05 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 15:18:20 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *msg)
{
	write(2, "minishell: ", 11);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

int	syntax_error(char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 48);
	if (token)
		write(2, token, ft_strlen(token));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
	return (0);
}
