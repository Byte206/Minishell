/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:27:38 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/25 10:46:41 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env *create_env_node(char *env_str);
static void  add_env_node(t_env **head, t_env *node);
static void  create_default_env(t_env **head);

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

static t_env *create_env_node(char *env_str)
{
	char    *name;
	char    *value;
	t_env   *node;

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
	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(name);
		free(value);
		return (NULL);
	}
	node->name = name;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

static void add_env_node(t_env **head, t_env *node)
{
	t_env *tail;

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

static void create_default_env(t_env **head)
{
	t_env *node;
	char *cwd;

	if (!head)
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->name = ft_strdup("PWD");
	cwd = getcwd(NULL, 0);
	if (cwd)
		node->value = cwd;
	else
		node->value = ft_strdup(".");
	node->prev = NULL;
	node->next = NULL;
	*head = node;
}
