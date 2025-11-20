/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:10:06 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/02 16:12:54 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

t_token			*new_token(void);
t_cmd			*new_cmd(void);
t_redir			*new_redir(void);
t_ast			*new_ast(void);
t_parser_state	*new_parser_state(void);
void			free_tokens(t_token *tokens);
void			free_cmd(t_cmd *cmd);
void			free_ast(t_ast *ast);
void			free_redir(t_redir *redir);
void			print_error(char *msg);
int				syntax_error(char *token);
void			print_ast(t_ast *ast);

#endif
