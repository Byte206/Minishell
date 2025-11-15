/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:47:53 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 18:54:39 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD && !current->joined)
			count++;
		else if (is_redir_token(current->type))
		{
			if (current->next)
				current = current->next;
		}
		current = current->next;
	}
	return (count);
}

void	add_cmd_to_ast(t_ast *ast, t_cmd *cmd)
{
	t_cmd	*current;

	if (!ast->commands)
	{
		ast->commands = cmd;
		return ;
	}
	current = ast->commands;
	while (current->next)
		current = current->next;
	current->next = cmd;
}

void	handle_word_token(t_token *token, char **argv, int *i)
{
	char	*tmp;

	if (token->joined && *i > 0)
	{
		tmp = ft_strjoin(argv[*i - 1], token->value);
		free(argv[*i - 1]);
		argv[*i - 1] = tmp;
	}
	else
	{
		argv[*i] = ft_strdup(token->value);
		(*i)++;
	}
}
