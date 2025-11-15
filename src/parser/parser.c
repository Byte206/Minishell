/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:33:21 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 16:00:01 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_redir_and_target(t_token **tokens)
{
	if ((*tokens)->next && (*tokens)->next->type == TOKEN_WORD)
	{
		*tokens = (*tokens)->next;
		while (*tokens && (*tokens)->next
			&& (*tokens)->next->type == TOKEN_WORD
			&& (*tokens)->next->joined)
			*tokens = (*tokens)->next;
	}
}

static char	**build_argv(t_token **tokens, int arg_count)
{
	char	**argv;
	int		i;

	argv = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
			handle_word_token(*tokens, argv, &i);
		else if (is_redir_token((*tokens)->type))
			skip_redir_and_target(tokens);
		*tokens = (*tokens)->next;
	}
	argv[i] = NULL;
	return (argv);
}

static void	process_redirections(t_cmd *cmd, t_token **tokens)
{
	t_redir	*redir;

	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if (is_redir_token((*tokens)->type))
		{
			redir = new_redir();
			redir->type = get_redir_type((*tokens)->type);
			if ((*tokens)->next && (*tokens)->next->type == TOKEN_WORD)
			{
				*tokens = (*tokens)->next;
				redir->target = build_redir_target(tokens);
				add_redir_to_cmd(cmd, redir);
				continue ;
			}
			add_redir_to_cmd(cmd, redir);
		}
		if (*tokens)
			*tokens = (*tokens)->next;
	}
}

static t_cmd	*parse_command(t_token **tokens)
{
	t_cmd	*cmd;
	int		arg_count;
	t_token	*start;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	start = *tokens;
	arg_count = count_args(start);
	cmd->argv = build_argv(tokens, arg_count);
	if (cmd->argv && cmd->argv[0])
		cmd->cmd_name = ft_strdup(cmd->argv[0]);
	*tokens = start;
	process_redirections(cmd, tokens);
	return (cmd);
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;
	t_token	*current;
	t_cmd	*cmd;

	if (!tokens || !validate_syntax(tokens))
		return (NULL);
	ast = new_ast();
	if (!ast)
		return (NULL);
	current = tokens;
	while (current)
	{
		cmd = parse_command(&current);
		if (cmd)
			add_cmd_to_ast(ast, cmd);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (ast);
}
