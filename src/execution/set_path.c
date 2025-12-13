/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:24:30 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/13 15:52:07 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_vars(t_env *env)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	return (count);
}

static char	*build_env_string(t_env *current)
{
	char	*env_str;
	size_t	total_len;

	total_len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
	env_str = malloc(total_len);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, current->name, total_len);
	ft_strlcat(env_str, "=", total_len);
	ft_strlcat(env_str, current->value, total_len);
	return (env_str);
}

char	**env_to_char_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		count;

	count = count_env_vars(env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env;
	count = 0;
	while (current)
	{
		if (current->value)
		{
			env_array[count] = build_env_string(current);
			if (!env_array[count])
				return (NULL);
			count++;
		}
		current = current->next;
	}
	env_array[count] = NULL;
	return (env_array);
}

char	*set_path(char *cmd_name, t_env *env)
{
	char	*cmd_path;

	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 5) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	cmd_path = get_cmd_path(cmd_name, env->value);
	if (!cmd_path)
		cmd_path = look_for_exec_in_cwd(cmd_name);
	return (cmd_path);
}
