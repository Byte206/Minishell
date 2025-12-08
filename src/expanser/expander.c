/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:22:32 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/08 23:33:01 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *str, int *len)
{
	int		i;
	char	*var_name;

	i = 0;
	if (str[i] == '?')
	{
		*len = 1;
		var_name = malloc(sizeof(char) * 2);
		var_name[0] = '?';
		var_name[1] = '\0';
		return (var_name);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*len = i;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*get_var_value(t_env *env, char *var_name, int *should_free,
		int exit_status)
{
	char	*value;

	*should_free = 0;
	if (ft_strcmp(var_name, "?") == 0)
	{
		*should_free = 1;
		return (ft_itoa(exit_status));
	}
	value = get_env_value(env, var_name);
	return (value);
}

static char	*process_variable(char *result, t_expand_ctx *ctx, int *i)
{
	char	*var_name;
	int		var_len;
	char	*temp;
	char	str_dollar[2];

	(*i)++;
	var_name = get_var_name(&ctx->str[*i], &var_len);
	if (var_name)
	{
		result = handle_valid_variable(result, var_name, ctx->env,
				ctx->exit_status);
		free(var_name);
		*i += var_len;
	}
	else
	{
		str_dollar[0] = '$';
		str_dollar[1] = '\0';
		temp = result;
		result = ft_strjoin(result, str_dollar);
		free(temp);
	}
	return (result);
}

static char	*expand_string(char *str, t_env *env, t_quote_type quote_t,
		int exit_status)
{
	char			*result;
	int				i;
	t_expand_ctx	ctx;

	ctx.str = str;
	ctx.env = env;
	ctx.exit_status = exit_status;
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && quote_t != QUOTE_SINGLE)
			result = process_variable(result, &ctx, &i);
		else
		{
			result = append_char_to_result(result, str[i]);
			i++;
		}
	}
	return (result);
}

void	expander(t_token *tokens, t_env *env, int exit_status)
{
	t_token	*current;
	char	*expanded;
	char    **parts;
	int     i;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_string(current->value, env, current->quote_type,
					exit_status);
			/* Field splitting: if unquoted and expansion introduces spaces,
			 * split into multiple TOKEN_WORD tokens so argv becomes [cmd, args]. */
			if (current->quote_type == QUOTE_NONE && expanded)
			{
				/* normalize tabs to spaces for splitting */
				i = 0;
				while (expanded[i])
				{
					if (expanded[i] == '\t')
						expanded[i] = ' ';
					i++;
				}
				parts = ft_split(expanded, ' ');
				if (parts && parts[0] && parts[1])
				{
					t_token *insert_after = current;
					t_token *newtok;
					int      j = 0;

					/* set current to first part */
					free(current->value);
					current->value = ft_strdup(parts[0]);
					current->joined = 0;
					/* insert subsequent parts as separate tokens */
					j = 1;
					while (parts[j])
					{
						if (parts[j][0] != '\0')
						{
							newtok = new_token();
							if (newtok)
							{
								newtok->value = ft_strdup(parts[j]);
								newtok->type = TOKEN_WORD;
								newtok->quote_type = QUOTE_NONE;
								newtok->joined = 0;
								newtok->next = insert_after->next;
								insert_after->next = newtok;
								insert_after = newtok;
							}
						}
						j++;
					}
				}
				else
				{
					/* no split needed or empty result */
					free(current->value);
					current->value = expanded;
					expanded = NULL; /* avoid double free below */
				}
				/* free temporary resources */
				if (parts)
				{
					i = 0;
					while (parts[i])
					{
						free(parts[i]);
						i++;
					}
					free(parts);
				}
				if (expanded)
					free(expanded);
			}
			else
			{
				free(current->value);
				current->value = expanded;
			}
		}
		current = current->next;
	}
}
