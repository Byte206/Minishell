/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tu_login <tu_email@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:24:35 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/30 08:47:11 by tu_login         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	handle_redir_in(t_redir *r)
{
    int fd;

    fd = open(r->target, O_RDONLY);
    if (fd < 0)
    {
        perror(r->target);
        return (-1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

static int	handle_redir_out(t_redir *r)
{
    int fd;

    fd = open(r->target, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror(r->target);
        return (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

static int	handle_redir_append(t_redir *r)
{
    int fd;

    fd = open(r->target, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror(r->target);
        return (-1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

static int	handle_heredoc(t_redir *r)
{
    int	pipefd[2];
    char	*line;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
            break ;
        if (ft_strncmp(line, r->target, ft_strlen(r->target) + 1) == 0)
        {
            free(line);
            break ;
        }
        ft_putendl_fd(line, pipefd[1]);
        free(line);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    return (0);
}


int set_redirections(t_redir *redirections)
{
    while (redirections)
    {
        if (redirections->type == REDIR_IN)
        {
            if (handle_redir_in(redirections) < 0)
                return (-1);
        }
        else if (redirections->type == REDIR_OUT)
        {
            if (handle_redir_out(redirections) < 0)
                return (-1);
        }
        else if (redirections->type == REDIR_APPEND)
        {
            if (handle_redir_append(redirections) < 0)
                return (-1);
        }
        else if (redirections->type == REDIR_HEREDOC)
        {
            if (handle_heredoc(redirections) < 0)
                return (-1);
        }
        redirections = redirections->next;
    }
    return (0);
}