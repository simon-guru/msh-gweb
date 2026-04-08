/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:00:00 by smayunga         #+#    #+#             */
/*   Updated: 2026/03/16 14:00:00 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "utils.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *sh, char **av, int in_child)
{
	int	status;

	write(1, "exit\n", 5);
	if (!av[1])
	{
		if (in_child)
			exit(sh->last_status);
		sh->running = 0;
		return (sh->last_status);
	}
	if (av[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	if (!is_numeric(av[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": numeric argument required\n", 28);
		if (in_child)
			exit(2);
		sh->running = 0;
		sh->last_status = 2;
		return (2);
	}
	status = ft_atoi(av[1]);
	if (in_child)
		exit(status);
	sh->running = 0;
	sh->last_status = status;
	return (status);
}
