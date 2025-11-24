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

static t_env    *find_next_min(t_env *env, t_env *start)
{
    t_env   *current = env;
    t_env   *min = NULL;

    while (current)
    {
        if ((!start || ft_strcmp(current->name, start->name) > 0)
            && (!min || ft_strcmp(current->name, min->name) < 0))
        {
            min = current;
        }
        current = current->next;
    }
    return (min);
}


static void print_env_var(t_env *env_var, int *first)
{
    if (!*first)
        printf("\n");
    printf("declare -x %s=\"%s\"", env_var->name, env_var->value);
    *first = 0;
}

int print_sorted_env(t_env **env)
{
    t_env   *min;
    t_env   *start;
    int     first;

    if (!env || !*env)
        return (0);
    start = NULL;
    first = 1;
    while (1)
    {
        min = find_next_min(*env, start);
        if (!min)
            break ;
        print_env_var(min, &first);
        start = min;
    }
    printf("\n");
    return (0);
}
