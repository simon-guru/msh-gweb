/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ext0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:31:14 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:31:29 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils.h"

void	helper_exec_child(t_shell *sh, t_cmd *c, int in, int out);

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

char	*ft_strjoin3(const char *a, const char *b, const char *c)
{
	char	*out;
	size_t	i;
	size_t	j;

	out = malloc(ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (a && a[j])
		out[i++] = a[j++];
	j = 0;
	while (b && b[j])
		out[i++] = b[j++];
	j = 0;
	while (c && c[j])
		out[i++] = c[j++];
	out[i] = 0;
	return (out);
}

void	helper_exec_child(t_shell *sh, t_cmd *c, int in, int out)
{
	if (in != 0)
		dup2(in, 0);
	if (out != 1)
		dup2(out, 1);
	if (apply_redirs(c->redirs, sh))
		exit(1);
	if (!c->argv[0])
		exit(0);
	if (is_builtin(c->argv[0]))
		exit(run_builtin(sh, c, 1));
}
