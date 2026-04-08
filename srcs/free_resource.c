/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resource.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:21:44 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:22:07 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

void	env_free(t_env *env)
{
	t_env	*n;

	while (env)
	{
		n = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = n;
	}
}

void	free_words(char **w)
{
	int	i;

	if (!w)
		return ;
	i = 0;
	while (w[i])
		free(w[i++]);
	free(w);
}

static void	free_redirs(t_redir *r)
{
	t_redir	*n;

	while (r)
	{
		n = r->next;
		free(r->target);
		free(r);
		r = n;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*n;

	while (cmd)
	{
		n = cmd->next;
		free_words(cmd->argv);
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = n;
	}
}

void	*xfree(void *p)
{
	if (p)
		free(p);
	return (NULL);
}
