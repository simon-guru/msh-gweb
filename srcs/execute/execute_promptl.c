/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_promptl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:27:55 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/16 13:59:53 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

extern void	helper_exec_child(t_shell *sh, t_cmd *c, int in, int out);

static void	exec_child(t_shell *sh, t_cmd *c, int in, int out)
{
	char	*path;
	char	**envv;

	setup_signals_child();
	helper_exec_child(sh, c, in, out);
	path = resolve_path(sh->env, c->argv[0]);
	if (!path)
	{
		printf("msh: %s: command not found\n", c->argv[0]);
		exit(127);
	}
	envv = env_to_array(sh->env);
	execve(path, c->argv, envv);
	free_words(envv);
	free(path);
	perror(c->argv[0]);
	exit(126);
}

static int	wait_all(int n)
{
	int	st;
	int	res;

	res = 0;
	while (n-- > 0)
	{
		wait(&st);
		if (WIFEXITED(st))
			res = WEXITSTATUS(st);
		else if (WIFSIGNALED(st))
			res = 128 + WTERMSIG(st);
	}
	return (res);
}

static int	exec_pipeline(t_shell *sh, t_cmd *c)
{
	int		fd[2];
	int		in;
	int		n;
	pid_t	pid;

	in = 0;
	n = 0;
	while (c && ++n)
	{
		if (c->next && pipe(fd) < 0)
			return (perror("pipe"), -1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), -1);
		if (pid == 0)
		{
			if (c->next)
				exec_child(sh, c, in, fd[1]);
			else
				exec_child(sh, c, in, 1);
		}
		if (in != 0)
			close(in);
		if (c->next)
		{
			close(fd[1]);
			in = fd[0];
		}
		c = c->next;
	}
	if (in != 0)
		close(in);
	return (wait_all(n));
}

int	exec_line(t_shell *sh, t_cmd *cmds)
{
	if (!cmds)
		return (0);
	if (!cmds->next && cmds->argv[0] && is_builtin(cmds->argv[0]))
		return (sh->last_status = run_builtin(sh, cmds, 0));
	sh->last_status = exec_pipeline(sh, cmds);
	return (sh->last_status);
}
