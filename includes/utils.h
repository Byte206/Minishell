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

#ifndef INIT_H
# define INIT_H

# include "structs.h" 

t_token *init_token(void);
t_redir *init_redir(void);
t_cmd   *init_cmd(void);
t_ast   *init_ast(void);


#endif