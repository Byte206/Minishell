/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:46:38 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/24 11:46:42 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	atoll_exit(char *str, int *error)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	*error = 0;
	i = skip_whitespace_and_sign(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(res, sign, str[i], error))
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
	return (res * sign);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (str[i] == '\0');
}

static void	exit_numeric_error(t_ast *ast, char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_ast(ast);
	exit(2);
}

int	ft_exit(t_ast *ast, int exit_code)
{
	uint8_t	new_exit_code;
	int		error;

	ft_putstr_fd("exit\n", 2);
	new_exit_code = 0;
	if (ast->commands->argv[1] && ast->commands->argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (!ast->commands->argv[1])
		new_exit_code = (uint8_t)exit_code;
	else if (!is_numeric(ast->commands->argv[1]))
		exit_numeric_error(ast, ast->commands->argv[1]);
	else
	{
		new_exit_code = (uint8_t)atoll_exit(ast->commands->argv[1], &error);
		if (error)
			exit_numeric_error(ast, ast->commands->argv[1]);
	}
	free_ast(ast);
	exit(new_exit_code);
}
