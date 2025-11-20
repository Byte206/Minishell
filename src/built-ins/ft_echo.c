/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 09:56:40 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 11:01:56 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **argv)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 3))
	{
		i = 2;
		new_line = 0;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
}
/*
int main()
{
	char *argv1[] = {"echo", "-n", "hola que tal", NULL};
	char *argv2[] = {"echo", "hay salto de linea", "hola que tal", NULL};

	echo(argv2);
	echo(argv1);
} */
