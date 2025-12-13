/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:27:38 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/13 15:45:58 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*create_env_node(char *env_str);
static void		add_env_node(t_env **head, t_env *node);
static void		create_default_env(t_env **head);

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	set_signals();
	env_list = NULL;
	i = 0;
	if (!envp || !envp[0])
	{
		create_default_env(&env_list);
		return (env_list);
	}
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (new_node)
			add_env_node(&env_list, new_node);
		i++;
	}
	return (env_list);
}

static t_env	*create_env_node(char *env_str)
{
	char	*name;
	char	*value;

	if (!env_str)
		return (NULL);
	name = get_name(env_str);
	value = get_value(env_str);
	if (!name || !value)
	{
		free(name);
		free(value);
		return (NULL);
	}
	return (build_node(name, value));
}

static void	add_env_node(t_env **head, t_env *node)
{
	t_env	*tail;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
	node->prev = tail;
}

static t_env	*create_simple_node(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	if (!node->name || !node->value)
	{
		free(node->name);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

static void	create_default_env(t_env **head)
{
	t_env	*pwd_node;
	t_env	*shlvl_node;
	t_env	*underscore_node;
	char	*cwd;

	if (!head)
		return ;
	pwd_node = malloc(sizeof(t_env));
	if (!pwd_node)
		return ;
	pwd_node->name = ft_strdup("PWD");
	cwd = getcwd(NULL, 0);
	if (cwd)
		pwd_node->value = cwd;
	else
		pwd_node->value = ft_strdup(".");
	pwd_node->prev = NULL;
	pwd_node->next = NULL;
	*head = pwd_node;
	shlvl_node = create_simple_node("SHLVL", "1");
	if (shlvl_node)
		add_env_node(head, shlvl_node);
	underscore_node = create_simple_node("_", "/usr/bin/env");
	if (underscore_node)
		add_env_node(head, underscore_node);
}
