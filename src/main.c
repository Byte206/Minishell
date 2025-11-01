/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:30:23 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/01 15:38:22 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		if (*input)
			add_history(input);
	}
	printf("exit\n");
	return (0);
}