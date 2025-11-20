/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:30:23 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/20 15:00:41 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_status = 0;

static void	print_env_list(t_env *env)
{
	t_env *cur = env;

	printf("--- ENV LIST DUMP ---\n");
	while (cur)
	{
		if (cur->name)
			printf("%s=", cur->name);
		else
			printf("(null)=");
		if (cur->value)
			printf("%s\n", cur->value);
		else
			printf("(null)\n");
		cur = cur->next;
	}
	printf("--- END ENV LIST ---\n");
}


int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	set_signals();

	/* Debug: print environment list created from envp */
	print_env_list(env);
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
					g_exit_status = execution(ast, &env);
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
