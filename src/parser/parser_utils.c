/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:47:53 by bmonterd          #+#    #+#             */
/*   Updated: 2025/12/13 14:05:35 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_token(t_token **current, int *count, int *word_started)
{
	if ((*current)->type == TOKEN_WORD)
	{
		if (!(*current)->joined || !(*word_started))
		{
			(*count)++;
			*word_started = 1;
		}
	}
	else if (is_redir_token((*current)->type))
	{
		if ((*current)->next)
			*current = (*current)->next;
		*word_started = 0;
	}
	else
		*word_started = 0;
}

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;
	int		word_started;

	count = 0;
	word_started = 0;
	current = tokens;
	while (current && current->type != TOKEN_PIPE)
	{
		process_token(&current, &count, &word_started);
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
