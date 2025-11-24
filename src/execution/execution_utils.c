/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:14:08 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/24 13:14:11 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void set_redirections(t_redir *redirections)
{
    t_redir *current;
    int     fd;

    current = redirections;
    while (current)
    {
        if (current->type == REDIR_INPUT)
        {
            fd = open(current->filename, O_RDONLY);
            if (fd < 0)
            {
                perror(current->filename);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (current->type == REDIR_OUTPUT)
        {
            fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(current->filename);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        // Handle other redirection types as needed
        current = current->next;
    }
} */
