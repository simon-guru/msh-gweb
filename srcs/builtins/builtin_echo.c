/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:00:00 by smayunga         #+#    #+#             */
/*   Updated: 2026/03/16 14:00:00 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "utils.h"

int	builtin_echo(char **av)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (av[i] && av[i][0] == '-' && av[i][1] == 'n')
	{
		if (!av[i][2])
		{
			nl = 0;
			i++;
		}
		else
			break ;
	}
	while (av[i])
	{
		write(1, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}
