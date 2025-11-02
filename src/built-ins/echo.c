/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 09:56:40 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 10:19:11 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	echo(char **argv)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	if (ft_strcmp(argv[1], "-n"))
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
		write(1, "\n", 1);
}

int main()
{
	char *argv1[] = {"echo", "-n", "hola que tal", NULL};
	char *argv2[] = {"echo", "hay salto de linea", "hola que tal", NULL};

	echo(argv1);
	printf("\n\n\n\n");
	echo(argv2);
}
