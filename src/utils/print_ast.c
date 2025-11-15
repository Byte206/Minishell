/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:22:47 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 19:04:10 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_redir(t_redir *redir)
{
	const char	*type_str[] = {"<", ">", ">>", "<<"};

	while (redir)
	{
		printf("    Redir: %s %s\n", type_str[redir->type], redir->target);
		redir = redir->next;
	}
}

static void	print_cmd(t_cmd *cmd, int cmd_num)
{
	int	i;

	printf("\n  Command %d:\n", cmd_num);
	printf("    Name: %s\n", cmd->cmd_name);
	printf("    Args: ");
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		printf("[%s] ", cmd->argv[i]);
		i++;
	}
	printf("\n");
	if (cmd->redirections)
		print_redir(cmd->redirections);
}

void	print_ast(t_ast *ast)
{
	t_cmd	*current;
	int		i;

	if (!ast)
	{
		printf("AST is NULL\n");
		return ;
	}
	printf("\n=== AST Structure ===\n");
	current = ast->commands;
	i = 1;
	while (current)
	{
		print_cmd(current, i);
		current = current->next;
		i++;
	}
	printf("\n====================\n");
}
