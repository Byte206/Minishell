/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:10:00 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/20 14:39:08 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include "structs.h"
# include "utils.h"
# include "lexer.h"
# include "parser.h"
//gabi
# include "built_ins.h"
# include <signal.h>
# include "execution.h"

extern int g_exit_status;

#endif
