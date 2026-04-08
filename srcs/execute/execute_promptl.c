/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_promptl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:27:55 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/16 15:00:00 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

static void	exec_child(t_shell *sh, t_cmd *c, int in, int out)
{
	char	*path;
	char	**envv;

	setup_signals_child();
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	if (apply_redirs(c->redirs, sh))
		exit(1);
	if (!c->argv[0])
		exit(0);
	if (is_builtin(c->argv[0]))
		exit(run_builtin(sh, c, 1));
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

static int	wait_all(int n, int *last_status)
{
	int	st;
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < n)
	{
		wait(&st);
		if (WIFEXITED(st))
			res = WEXITSTATUS(st);
		else if (WIFSIGNALED(st))
			res = 128 + WTERMSIG(st);
		i++;
	}
	if (last_status)
		*last_status = res;
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
	return (wait_all(n, &sh->last_status));
}

int	exec_line(t_shell *sh, t_cmd *cmds)
{
	t_cmd	*c;
	int		n_cmds;

	if (!cmds)
		return (0);
	n_cmds = 0;
	c = cmds;
	while (c)
	{
		n_cmds++;
		c = c->next;
	}
	if (n_cmds == 1 && cmds->argv[0] && is_builtin(cmds->argv[0]))
	{
		if (apply_redirs(cmds->redirs, sh))
			return (sh->last_status = 1);
		return (sh->last_status = run_builtin(sh, cmds, 0));
	}
	sh->last_status = exec_pipeline(sh, cmds);
	return (sh->last_status);
}
