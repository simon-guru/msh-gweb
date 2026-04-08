/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:00:00 by smayunga         #+#    #+#             */
/*   Updated: 2026/03/16 14:00:00 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "utils.h"

int	builtin_cd(t_shell *sh, char **av)
{
	char	*path;

	if (!av[1] || !ft_strcmp(av[1], "--"))
		path = env_get(sh->env, "HOME");
	else if (av[2])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	else
		path = av[1];
	if (!path || !*path)
		return (0);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
