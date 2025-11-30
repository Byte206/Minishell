/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byte <byte@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:24:30 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/30 13:34:36 by byte             ###   ########.fr       */
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
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_to_char_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		count;
	size_t	total_len;

	count = count_env_vars(env);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env;
	count = 0;
	while (current)
	{
		total_len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
		env_array[count] = malloc(total_len);
		if (!env_array[count])
			return (NULL);
		ft_strlcpy(env_array[count], current->name, total_len);
		ft_strlcat(env_array[count], "=", total_len);
		ft_strlcat(env_array[count], current->value, total_len);
		count++;
		current = current->next;
	}
	env_array[count] = NULL;
	return (env_array);
}

// Función para liberar el array de strings
void	free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*get_cmd_path(char *cmd_name, char *path_value)
{
	char	**paths;
	char	*full_path;
	size_t	i;
	size_t	total_len;

	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		total_len = ft_strlen(paths[i]) + ft_strlen(cmd_name) + 2;
		full_path = malloc(total_len);
		if (!full_path)
			return (free_array(paths), NULL);
		ft_strlcpy(full_path, paths[i], total_len);
		ft_strlcat(full_path, "/", total_len);
		ft_strlcat(full_path, cmd_name, total_len);
		if (access(full_path, X_OK) == 0)
			return (free_array(paths), full_path);
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*set_path(char *cmd_name, t_env *env)
{
	char	*cmd_path;

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
