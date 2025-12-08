/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:49:30 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/08 23:42:58 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*handle_valid_variable(char *result, char *var_name, t_env *env,
			int exit_status);
char	*append_char_to_result(char *result, char c);
char	*get_env_value(t_env *env, char *name);
void	expander(t_token *tokens, t_env *env, int exit_status);
char	*get_var_name(char *str, int *len);
char	*get_var_value(t_env *env, char *var_name, int *should_free,
			int exit_status);
void	apply_field_splitting(t_token *current, char *expanded);
