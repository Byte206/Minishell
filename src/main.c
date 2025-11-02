/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:30:23 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/02 14:53:21 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    // t_env   *env; Gab
    char    *input;
    t_token *tokens;
    t_ast   *ast;
    
    (void)argc;
    (void)argv;
    // g_exit_code = 0; Gab used on signals
    // env = init_env(envp); Gab
    // setup_signals(); Gab signals
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (*input)
        {
            add_history(input);
            // tokens = tokenize(input); Bast
            // if (tokens)
            // {
            //     ast = parse(tokens); Bast
            //     if (ast)
            //     {
            //         g_exit_code = execute(ast, env); Gab
            //         free_ast(ast);
            //     }
            //     free_tokens(tokens); Bast
            // }
        }
        free(input);
    }
    printf("exit\n");
    // free_env(env); Gab
    return (1/*g_exit_code*/);  //Gab signals
}