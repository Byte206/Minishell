/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:38:53 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/23 20:02:08 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Environment variable linked list
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

// env functions
t_env				*init_env(char **envp);
char				*get_name(char *var);
char				*get_value(char *var);

// execution
int					execution(t_ast *ast, t_env **env, int exit_code);

// built-in functions
int					ft_pwd(t_cmd *cmd);
int					ft_echo(char **argv);
int					ft_cd(t_cmd *cmd, t_env **env);
int					ft_env(t_cmd *cmd, t_env **env);
int					ft_exit(t_ast *ast, int exit_code);
int					ft_export(t_cmd *cmd, t_env **env);
int					print_sorted_env(t_env **env);
int					ft_unset(t_cmd *cmd, t_env **env);

// set_path functions
char				*look_for_exec_in_cwd(char *cmd_name);
char				*set_path(char *cmd_name, t_env *env);
