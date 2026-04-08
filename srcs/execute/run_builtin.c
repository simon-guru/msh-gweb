/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:28:34 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:28:45 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

int	run_builtin(t_shell *sh, t_cmd *cmd, int in_child)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(sh->env));
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(sh, cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(sh, cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(sh, cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (builtin_exit(sh, cmd->argv, in_child));
	return (1);
}

int	is_builtin(const char *s)
{
	if (!s)
		return (0);
	return (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env") || !ft_strcmp(s, "exit"));
}
