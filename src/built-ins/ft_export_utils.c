/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:07:10 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/24 15:07:12 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_env_nodes(t_env *env)
{
    t_env   *current;
    int     count;

    count = 0;
    current = env;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

int print_sorted_env(t_env **env)
{
    char    **env_array;
    int     i;
    int     count;

    count = count_env_nodes(*env);
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (1);
    while(i < count)
    {
        env_array[i] = malloc(sizeof(char) * (get_node_len(env))); // assuming max length
        if (!env_array[i])
            return (1);
        copy_node_to_array(env, env_array[i], i);
        env = env->next;
        i++;
    }
    env_array[i] = NULL;
    sort_env_array(env_array, count);
}
