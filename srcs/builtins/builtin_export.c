/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:00:00 by smayunga         #+#    #+#             */
/*   Updated: 2026/03/16 14:00:00 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "utils.h"

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (!((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || *s == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_export(t_shell *sh, char **av)
{
	char	*eq;
	char	*key;
	char	*value;
	int		i;

	if (!av[1])
	{
		while (sh->env)
		{
			write(1, "declare -x ", 11);
			write(1, sh->env->key, ft_strlen(sh->env->key));
			write(1, "=\"", 2);
			write(1, sh->env->value, ft_strlen(sh->env->value));
			write(1, "\"\n", 2);
			sh->env = sh->env->next;
		}
		return (0);
	}
	i = 1;
	while (av[i])
	{
		eq = ft_strchr(av[i], '=');
		if (!eq)
		{
			if (!is_valid_identifier(av[i]))
			{
				write(2, "minishell: export: `", 21);
				write(2, av[i], ft_strlen(av[i]));
				write(2, "': not a valid identifier\n", 28);
				return (1);
			}
			env_set(&sh->env, av[i], "");
		}
		else
		{
			key = ft_substr(av[i], 0, eq - av[i]);
			if (!is_valid_identifier(key))
			{
				free(key);
				write(2, "minishell: export: `", 21);
				write(2, av[i], ft_strlen(av[i]));
				write(2, "': not a valid identifier\n", 28);
				return (1);
			}
			value = ft_strdup(eq + 1);
			env_set(&sh->env, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (0);
}
