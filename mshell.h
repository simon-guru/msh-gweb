/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:17:09 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/16 13:47:29 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MSHELL_H
# define MSHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_sig;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	int		running;
}	t_shell;

/* env */
t_env	*env_from_array(char **envp);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *value);
int		env_unset(t_env **env, const char *key);
char	**env_to_array(t_env *env);

/* parser */
char	**lex_line(const char *line, t_shell *sh, int *tokc);
t_cmd	*parse_cmds(char **tk, int n);

/* execution */
int		exec_line(t_shell *sh, t_cmd *cmds);
int		is_builtin(const char *s);
int		run_builtin(t_shell *sh, t_cmd *cmd, int in_child);
char	*resolve_path(t_env *env, const char *cmd);

/* builtins */
int		builtin_pwd(void);
int		builtin_env(t_env *env);
int		builtin_echo(char **av);
int		builtin_cd(t_shell *sh, char **av);
int		builtin_export(t_shell *sh, char **av);
int		builtin_unset(t_shell *sh, char **av);
int		builtin_exit(t_shell *sh, char **av, int in_child);

/* signals */
void	setup_signals_interactive(void);
void	setup_signals_child(void);

/* main helpers */
int		has_unclosed_quotes(const char *s);

/* cleanups */
void	free_cmds(t_cmd *cmd);
void	free_words(char **w);
void	env_free(t_env *env);

/* expand */
char	*expand_name(const char *s, int *i, t_shell *sh);

/* redirs */
int		apply_redirs(t_redir *r, t_shell *sh);

#endif
