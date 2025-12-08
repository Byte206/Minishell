/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:30:23 by bmonterd          #+#    #+#             */
/*   Updated: 2025/12/09 00:06:10 by gamorcil         ###   ########.fr       */
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

static void	process_input(char *input, t_env **env, int *exit_code)
{
	t_token	*tokens;
	t_ast	*ast;

	if (*input)
	{
		add_history(input);
		tokens = lexer(input);
		if (tokens)
		{
			expander(tokens, *env, *exit_code);
			ast = parser(tokens);
			free_tokens(tokens);
			if (ast)
			{
				*exit_code = execution(ast, env, *exit_code);
				free_ast(ast);
			}
		}
	}
}

static void	shell_loop(t_env **env, int *exit_code)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		process_input(input, env, exit_code);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		exit_code;

	exit_code = 0;
	if (argc != 1 || argv[1])
		return (1);
	env = init_env(envp);
	printf("Welcome to minishell\n");
	shell_loop(&env, &exit_code);
	free_env(env);
	return (0);
}
