/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:37:34 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/25 10:39:37 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_value_from_env(const char *name, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*get_old_path(t_env **env)
{
	char	*cwd;
	char	*pwd_value;

	cwd = getcwd(NULL, 0);
	if (cwd)
		return (cwd);
	pwd_value = get_value_from_env("PWD", env);
	if (pwd_value)
		return (ft_strdup(pwd_value));
	return (NULL);
}

static char	*get_target_path(char *path, char *old_path, t_env **env)
{
	char	*target_path;

	if (!path)
	{
		target_path = get_value_from_env("HOME", env);
		if (!target_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (ft_strdup(target_path));
	}
	if (ft_strcmp(path, "-") == 0)
	{
		target_path = get_value_from_env("OLDPWD", env);
		if (!target_path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		printf("%s\n", target_path);
		return (ft_strdup(target_path));
	}
	return (ft_strdup(path));
}

void	update_env_path(t_env **env, char *old_path)
{
	t_env	*current;
	char	*new_cwd;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
		return ;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(old_path);
		}
		else if (ft_strcmp(current->name, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_cwd);
		}
		current = current->next;
	}
	free(new_cwd);
}

int	ft_cd(t_cmd *cmd, t_env **env)
{
	char	*new_path;
	char	*old_path;

	if (cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	old_path = get_old_path(env);
	new_path = get_target_path(cmd->argv[1], old_path, env);
	if (!new_path)
	{
		free(old_path);
		return (1);
	}
	if (chdir(new_path) == -1)
	{
		perror("minishell: cd");
		free(new_path);
		free(old_path);
		return (1);
	}
	update_env_path(env, old_path);
	return (free(old_path), free(new_path), 0);
}
