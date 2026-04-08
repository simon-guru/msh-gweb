/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:26:47 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:27:08 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

static t_env	*env_new(char *k, char *v)
{
	t_env	*n;

	n = malloc(sizeof(t_env));
	if (!n)
		return (NULL);
	n->key = k;
	n->value = v;
	n->next = NULL;
	return (n);
}

t_env	*env_from_array(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	char	*eq;
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	while (envp[++i])
	{
		eq = envp[i];
		while (*eq && *eq != '=')
			eq++;
		if (!*eq)
			continue ;
		node = env_new(ft_substr(envp[i], 0, eq - envp[i]),
				ft_strdup(eq + 1));
		if (!node)
			return (env_free(head), NULL);
		if (!tail)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
	}
	return (head);
}

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*try_dirs(char *path, const char *cmd)
{
	int		i;
	int		j;
	char	dir[4096];
	char	*full;

	i = 0;
	while (1)
	{
		j = 0;
		while (path[i] && path[i] != ':')
			dir[j++] = path[i++];
		dir[j] = 0;
		full = ft_strjoin3(dir, "/", cmd);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		if (!path[i])
			break ;
		i++;
	}
	return (NULL);
}

char	*resolve_path(t_env *env, const char *cmd)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path = env_get(env, "PATH");
	if (!path)
		return (NULL);
	return (try_dirs(path, cmd));
}
