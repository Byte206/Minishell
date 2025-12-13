/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:00:00 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/11 20:00:00 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*append_value(char *result, char *var_value)
{
	int	j;

	j = 0;
	while (var_value[j])
		result = append_char_to_result(result, var_value[j++]);
	return (result);
}

static char	*process_var_value(char *result, char *var_value, int should_free)
{
	if (!var_value)
		return (result);
	result = append_value(result, var_value);
	if (should_free)
		free(var_value);
	return (result);
}

static char	*expand_var(char *result, char **line, int *i,
				t_heredoc_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		should_free;

	(*i)++;
	var_name = get_var_name(&(*line)[*i], &var_len);
	if (var_name)
	{
		var_value = get_var_value(ctx->env, var_name, &should_free,
				ctx->exit_code);
		result = process_var_value(result, var_value, should_free);
		free(var_name);
		*i += var_len;
	}
	else
		result = append_char_to_result(result, '$');
	return (result);
}

char	*expand_heredoc_line(char *line, t_env *env, int exit_code)
{
	char			*result;
	int				i;
	t_heredoc_ctx	ctx;

	ctx.env = env;
	ctx.exit_code = exit_code;
	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			result = expand_var(result, &line, &i, &ctx);
		else
		{
			result = append_char_to_result(result, line[i]);
			i++;
		}
	}
	return (result);
}
