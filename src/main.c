/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:30:23 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 21:52:25 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			tokens = lexer(input);
			if (tokens)
			{
				print_tokens(tokens);
				// expander(tokens, envp);
				ast = parser(tokens);
				if (ast)
				{
					print_ast(ast);
					free_ast(ast);
				}
				free_tokens(tokens);
			}
		}
		free(input);
	}
	printf("exit\n");
	return (0);
}
