/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:15:42 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 16:00:01 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_ast			*parser(t_token *tokens);
int				validate_syntax(t_token *tokens);
int				is_redir_token(t_token_type type);
int				count_args(t_token *tokens);
t_redir_type	get_redir_type(t_token_type type);
void			add_redir_to_cmd(t_cmd *cmd, t_redir *redir);
void			add_cmd_to_ast(t_ast *ast, t_cmd *cmd);
void			handle_word_token(t_token *token, char **argv, int *i);
char			*build_redir_target(t_token **tokens);

#endif
