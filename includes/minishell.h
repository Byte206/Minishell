/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byte <byte@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:10:00 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/27 20:36:02 by byte             ###   ########.fr       */
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
# include <signal.h>
# include "execution.h"
# include <fcntl.h>
# include <stdint.h>
# include <limits.h>
#include <sys/wait.h>
//expanser
# include "expander.h"

extern int g_signal;

#endif
