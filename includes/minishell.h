/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_login <tu_email@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:10:00 by bmonterd          #+#    #+#             */
/*   Updated: 2025/11/30 08:34:40 by tu_login         ###   ########.fr       */
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
# include <sys/wait.h>
//expanser
# include "expander.h"

extern int g_signal;

#endif
