/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamorcil <gamorcil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:38:53 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/01 13:53:36 by gamorcil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env functions
t_env				*init_env(char **envp);
char				*get_name(char *var);
char				*get_value(char *var);

// execution
int					execution(t_ast *ast, t_env **env, int exit_code);
int					execute_multiple_commands(t_ast *ast, t_env **env);
int					exec_builtin(t_ast *ast, t_env **env, int exit_code);
void				child_execute(t_cmd *cmd, int prev_read, int pipe_write,
						t_env **env);

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

// exec_builtin functions
int					exec_builtin_cmd(t_ast *ast, t_env **env, int exit_code);

// execution_utils functions
int					is_builtin(char *cmd_name);
int					count_cmds(t_cmd *cmd);
int					wait_children(int *pids, int n);
void				handle_parent_pipes(int *prev_read, int pipefd[2],
						int has_next);

// pipes functions
int					spawn_pipeline(t_ast *ast, t_env **env, int *pids);

// signla
void				set_signals(void);
void				set_child_signals(void);
void				set_execution_signals(void);
