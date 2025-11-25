/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:07:10 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/25 10:43:36 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	env_size(t_env *env)
{
	int		i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static int	safe_cmp(t_env *a, t_env *b)
{
	if (!a->name && !b->name)
		return (0);
	if (!a->name)
		return (1);
	if (!b->name)
		return (-1);
	return (strcmp(a->name, b->name));
}

static void	swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sort_env(t_env **arr, int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (safe_cmp(arr[j], arr[j + 1]) > 0)
				swap_env(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

void	print_env_sorted(t_env *env)
{
	int		i;
	int		size;
	t_env	**arr;

	if (!env)
		return ;
	size = env_size(env);
	if (size <= 0)
		return ;
	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return ;
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	sort_env(arr, size);
	i = 0;
	while (i < size)
	{
		if (arr[i]->name)
		{
			if (arr[i]->value)
				printf("%s=%s\n", arr[i]->name, arr[i]->value);
			else
				printf("%s\n", arr[i]->name);
		}
		i++;
	}
	free(arr);
}
