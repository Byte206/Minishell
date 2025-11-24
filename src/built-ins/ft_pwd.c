/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:54:16 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/02 11:00:46 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 	ft_pwd(t_cmd *cmd)
{
	char	*path;

	if (cmd->argv
		&& cmd->argv[1] != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		//g_exit_status = 1;
		return (1);
	}
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	return (0);
}
/*
int main()
{
	ft_pwd();
} */
