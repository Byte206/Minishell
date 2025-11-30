/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byte <byte@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:38:53 by gamorcil          #+#    #+#             */
/*   Updated: 2025/11/30 13:32:40 by byte             ###   ########.fr       */
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
int					execute_multiple_commands(t_ast *ast, t_env **env);

// built-in functions
int					ft_pwd(t_cmd *cmd);
int					ft_echo(char **argv);
int					ft_cd(t_cmd *cmd, t_env **env);
int					ft_env(t_cmd *cmd, t_env **env);
int					ft_exit(t_ast *ast, int exit_code);
int					ft_export(t_cmd *cmd, t_env **env);
int					print_env_sorted(t_env **env);
int					ft_unset(t_cmd *cmd, t_env **env);

// set_path functions
char				*look_for_exec_in_cwd(char *cmd_name);
char				*set_path(char *cmd_name, t_env *env);
char				**env_to_char_array(t_env *env);

// Redir functions
int					set_redirections(t_redir *redirections);

// signla
void				set_signals(void);
