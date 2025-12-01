/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:19:56 by bmonterd          #+#    #+#             */
/*   Updated: 2025/12/01 13:50:38 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}					t_quote_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote_type;
	int				joined;
	struct s_token	*next;
}					t_token;

typedef struct s_parser_state
{
	t_token			*current;
}					t_parser_state;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**argv;
	t_redir			*redirections;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ast
{
	t_cmd			*commands;
}					t_ast;

// Environment variable linked list
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_expand_ctx
{
	char			*str;
	t_env			*env;
	int				exit_status;
}					t_expand_ctx;

#endif
