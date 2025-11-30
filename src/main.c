/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:30:23 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/30 19:05:11 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal = 0;

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;
	t_env	*env;
	int		exit_code;

	exit_code = 0;
	if (argc != 1 || argv[1])
		return (1);
	env = init_env(envp);
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
				expander(tokens, env, exit_code);
				ast = parser(tokens);
				free_tokens(tokens);
				free(input);
				if (ast)
				{
					exit_code = execution(ast, &env, exit_code);
					free_ast(ast);
				}
			}
		}
	}
	free_env(env);
	return (0);
}
