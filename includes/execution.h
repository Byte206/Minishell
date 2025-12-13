/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmonterd <bmonterd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:38:53 by gamorcil          #+#    #+#             */
/*   Updated: 2025/12/13 15:24:12 by bmonterd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env functions
t_env	*init_env(char **envp);
char	*get_name(char *var);
char	*get_value(char *var);
t_env	*build_node(char *name, char *value);

// execution
int		execution(t_ast *ast, t_env **env, int exit_code);
int		execute_multiple_commands(t_ast *ast, t_env **env, int exit_code);
int		exec_builtin(t_ast *ast, t_env **env, int exit_code);
void	child_execute(t_cmd *cmd, int prev_read, int pipe_write, t_env **env);

// built-in functions
int		ft_pwd(t_cmd *cmd);
int		ft_echo(char **argv);
int		ft_cd(t_cmd *cmd, t_env **env);
int		ft_env(t_cmd *cmd, t_env **env);
int		ft_exit(t_ast *ast, int exit_code);
int		ft_export(t_cmd *cmd, t_env **env);
int		print_env_sorted(t_env **env);
int		ft_unset(t_cmd *cmd, t_env **env);

// ft_cd_utils functions
char	*get_value_from_env(const char *name, t_env **env);

// ft_exit_utils functions
int		check_overflow(long long res, int sign, char digit, int *error);
int		skip_whitespace_and_sign(char *str, int *sign);

// set_path functions
char	*look_for_exec_in_cwd(char *cmd_name);
char	*set_path(char *cmd_name, t_env *env);
char	**env_to_char_array(t_env *env);
void	free_array(char **array);
char	*build_full_path(char *dir, char *cmd_name);
char	*get_cmd_path(char *cmd_name, char *path_value);

// Redir functions
int		set_redirections(t_redir *redirections);
int		process_heredoc(t_redir *r, t_env *env, int exit_code);
int		process_all_heredocs(t_ast *ast, t_env *env, int exit_code);
void	close_heredoc_fds(t_ast *ast);
int		handle_redir_in(t_redir *r);
int		handle_redir_out(t_redir *r);
int		handle_redir_append(t_redir *r);
int		handle_heredoc(t_redir *r);
char	*expand_heredoc_line(char *line, t_env *env, int exit_code);

// exec_builtin functions
int		exec_builtin_cmd(t_ast *ast, t_env **env, int exit_code);

// execution_utils functions
int		is_builtin(char *cmd_name);
int		father(int pid);
int		exec_external_cmd(t_ast *ast, t_env **env);
int		handle_redir_only_cmd(t_ast *ast);
int		exec_single_cmd(t_ast *ast, t_env **env, int exit_code);

// ft_export_utils2 functions
void	add_or_update_env(t_env **env, char *name, char *value);
void	export_not_valid(char *name);
int		is_valid_identifier(char *name);
void	free_export_vars(char *name, char *value);
int		handle_export_without_equal(t_cmd *cmd, t_env **env, int i);
int		handle_export_with_equal(t_cmd *cmd, t_env **env, int i);
int		count_cmds(t_cmd *cmd);
int		wait_children(int *pids, int n);
void	handle_parent_pipes(int *prev_read, int pipefd[2], int has_next);

// pipes functions
int		spawn_pipeline(t_ast *ast, t_env **env, int *pids);

// signla
void	set_signals(void);
void	set_child_signals(void);
void	set_execution_signals(void);
