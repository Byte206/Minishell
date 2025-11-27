/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:24:35 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/27 12:25:31 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	handle_redir_in(t_redir *r)
{
    int fd;

    fd = open(r->target, O_RDONLY);
    if (fd < 0)
    {
        perror(r->target);
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

static void	handle_redir_out(t_redir *r)
{
    int fd;

    fd = open(r->target, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror(r->target);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void	handle_redir_append(t_redir *r)
{
    int fd;

    fd = open(r->target, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror(r->target);
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void	handle_heredoc(t_redir *r)
{
    int	pipefd[2];
    char	*line;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
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
        write(pipefd[1], line, ft_strlen(line));
        write(pipefd[1], "\n", 1);
        free(line);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
}


void set_redirections(t_redir *redirections)
{
    while (redirections)
    {
        if (redirections->type == REDIR_IN)
            handle_redir_in(redirections);
        else if (redirections->type == REDIR_OUT)
            handle_redir_out(redirections);
        else if (redirections->type == REDIR_APPEND)
            handle_redir_append(redirections);
        else if (redirections->type == REDIR_HEREDOC)
            handle_heredoc(redirections);
        redirections = redirections->next;
    }
}