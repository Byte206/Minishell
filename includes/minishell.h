/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byte <byte@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:10:00 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/30 13:32:48 by byte             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "structs.h"
# include "utils.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// gabi
# include "execution.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdint.h>
# include <sys/wait.h>
// expanser
# include "expander.h"

extern int	g_signal;

#endif
