/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:07:10 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/25 11:09:04 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static t_env	**create_env_array(t_env *env, int size)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

// Función para ordenar el array (bubble sort)
static void	sort_env_array(t_env **arr, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j]->name, arr[j + 1]->name) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

// Función para imprimir una variable de entorno
static void	print_env_var(t_env *node)
{
	printf("declare -x %s", node->name);
	if (node->value && node->value[0])
		printf("=\"%s\"", node->value);
	printf("\n");
}

int	print_env_sorted(t_env **env)
{
	t_env	**arr;
	int		size;
	int		i;

	if (!env || !*env)
		return (1);
	size = count_env_nodes(*env);
	arr = create_env_array(*env, size);
	if (!arr)
		return (1);
	sort_env_array(arr, size);
	i = 0;
	while (i < size)
	{
		print_env_var(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
