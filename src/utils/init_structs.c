/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:09:19 by bmonterd          #+#    #+#             */
/*   Updated: 2025/12/11 19:11:31 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = NULL;
	token->type = TOKEN_WORD;
	token->quote_type = QUOTE_NONE;
	token->joined = 0;
	token->next = NULL;
	return (token);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = NULL;
	cmd->argv = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_IN;
	redir->target = NULL;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

t_ast	*new_ast(void)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->commands = NULL;
	return (ast);
}

t_parser_state	*new_parser_state(void)
{
	t_parser_state	*state;

	state = (t_parser_state *)malloc(sizeof(t_parser_state));
	if (!state)
		return (NULL);
	state->current = NULL;
	return (state);
}
