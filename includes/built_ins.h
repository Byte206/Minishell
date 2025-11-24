/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:01:46 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/03 14:03:01 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Environment variable linked list
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

//env functions
t_env	*init_env(char **envp);
char 	*get_name(char *var);
char 	*get_value(char *var);

// built-in functions

int 	ft_pwd(t_cmd *cmd);
int		ft_echo(char **argv);
int		ft_cd(t_cmd *cmd, t_env **env);
int		ft_env(t_cmd *cmd, t_env **env);
int		ft_exit(t_cmd *cmd);
int		ft_export(t_cmd *cmd, t_env **env);
int		ft_unset(t_cmd *cmd, t_env **env);