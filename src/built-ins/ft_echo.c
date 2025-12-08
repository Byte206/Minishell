/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 09:56:40 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/08 23:23:07 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i += 2;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (0);
		else
			return (1);
	}
	return (1);
}

int	ft_echo(char **argv)
{
	int	new_line;
	int	i;

	i = 1;
	new_line = check_newline(argv[1]);
	if (new_line == 0)
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}
/*
int main()
{
	char *argv1[] = {"echo", "-n", "hola que tal", NULL};
	char *argv2[] = {"echo", "hay salto de linea", "hola que tal", NULL};

	echo(argv2);
	echo(argv1);
} */
