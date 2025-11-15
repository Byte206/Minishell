/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:23:14 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/15 15:15:16 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

t_token	*lexer(char *input);
void	add_token_to_list(t_token **head, t_token *new_token);
t_token	*get_next_token(char **input);
t_token	*create_pipe_token(char **input);
t_token	*create_redir_in_token(char **input);
t_token	*create_redir_out_token(char **input);
t_token	*create_word_token(char **input);
t_token	*create_quoted_token(char **input, char quote_char);
void	skip_whitespace(char **input);
int		is_separator(char c);
void	print_tokens(t_token *tokens);

#endif
