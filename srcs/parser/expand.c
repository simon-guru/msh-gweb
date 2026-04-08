/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:29:11 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:29:23 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

char	*expand_name(const char *s, int *i, t_shell *sh)
{
	int		st;
	char	*key;
	char	*val;

	if (s[*i] == '?')
		return ((*i)++, ft_itoa(sh->last_status));
	st = *i;
	while (s[*i] && ft_isalnum(s[*i]))
		(*i)++;
	if (*i == st)
		return (ft_strdup(""));
	key = ft_substr(s, st, *i - st);
	val = env_get(sh->env, key);
	free(key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}
