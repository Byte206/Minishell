/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byte <byte@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:57:03 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/30 13:32:30 by byte             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*build_full_path(char *dir, char *cmd_name)
{
	char	*full_path;
	size_t	total_len;

	total_len = ft_strlen(dir) + ft_strlen(cmd_name) + 2;
	full_path = malloc(total_len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, total_len);
	ft_strlcat(full_path, "/", total_len);
	ft_strlcat(full_path, cmd_name, total_len);
	return (full_path);
}

static char	*check_path_in_dir(char *dir, char *cmd_name, char **paths)
{
	char	*full_path;

	full_path = build_full_path(dir, cmd_name);
	if (!full_path)
	{
		free_array(paths);
		return (NULL);
	}
	if (access(full_path, X_OK) == 0)
	{
		free_array(paths);
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

char	*get_cmd_path(char *cmd_name, char *path_value)
{
	char	**paths;
	char	*result;
	size_t	i;

	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		result = check_path_in_dir(paths[i], cmd_name, paths);
		if (result)
			return (result);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*look_for_exec_in_cwd(char *cmd_name)
{
	char	*cwd;
	char	*temp;
	char	*full_path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	temp = ft_strjoin(cwd, "/");
	free(cwd);
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
