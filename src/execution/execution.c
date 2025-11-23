/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:34:58 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/23 20:14:57 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_builtin(char *cmd_name)
{
    size_t len;

    len = ft_strlen(cmd_name);
    if ((ft_strncmp(cmd_name, "cd", len) == 0 && len == 2) ||
        (ft_strncmp(cmd_name, "echo", len) == 0 && len == 4) ||
        (ft_strncmp(cmd_name, "env", len) == 0 && len == 3) ||
        (ft_strncmp(cmd_name, "exit", len) == 0 && len == 4) ||
        (ft_strncmp(cmd_name, "export", len) == 0 && len == 6) ||
        (ft_strncmp(cmd_name, "pwd", len) == 0 && len == 3) ||
        (ft_strncmp(cmd_name, "unset", len) == 0 && len == 5))
        return (1);
    return (0);
}
/*
static int exec_builtin(t_ast *ast, t_env **env)
{
	if (ft_strcmp(ast->commands->cmd_name, "cd") == 0)
		return (ft_cd(ast->commands, env));
	else if (ft_strcmp(ast->commands->cmd_name, "echo") == 0)
		return (ft_echo(ast->commands));
	else if (ft_strcmp(ast->commands->cmd_name, "env") == 0)
		return (ft_env(ast->commands, env));
	else if (ft_strcmp(ast->commands->cmd_name, "exit") == 0)
		return (ft_exit(ast->commands));
	else if (ft_strcmp(ast->commands->cmd_name, "export") == 0)
		return (ft_export(ast->commands, env));
	else if (ft_strcmp(ast->commands->cmd_name, "pwd") == 0)
		return (ft_pwd(ast->commands));
	else if (ft_strcmp(ast->commands->cmd_name, "unset") == 0)
		return (ft_unset(ast->commands, env)); 
} */

static int count_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static int exec_single_cmd(t_ast *ast, t_env **env)
{
	pid_t	pid;
	char	*path;
	
	if (is_builtin(ast->commands->cmd_name))
		return (exec_builtin(ast, env));
	pid = fork();
	if (pid == 0)
	{
		set_signals_child();
		set_redirections(ast->commands->redirections);
		
		path = set_path(ast->commands->cmd_name, *env);
		if (!path)
		{
			//comand not found return;
		}
		execve(path, ast->commands->argv, env_to_char_array(*env));
		perror("execve");
		exit(127);
	}
	
}

int	execution(t_ast *ast, t_env **env)
{
	int cmd_count;
	
	if (!ast)
		return (1);
	cmd_count = count_cmd(ast->commands);
	//printf("Command count:%d\n", cmd_count);
	if (cmd_count == 0)
		return (0);
	if (cmd_count == 1)
		return (exec_single_cmd(ast, env));
	return (exec_with_pipe(ast, env));
	return (0);
}