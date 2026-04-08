/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:27:18 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:27:34 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

/*
** Algoritmo: atualiza se chave existe; senao adiciona no fim.
** Motivo: comportamento esperado do built-in export simples.
*/
int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*cur;
	t_env	*newn;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (free(cur->value), cur->value = ft_strdup(value), 0);
		if (!cur->next)
			break ;
		cur = cur->next;
	}
	newn = malloc(sizeof(t_env));
	if (!newn)
		return (1);
	newn->key = ft_strdup(key);
	newn->value = ft_strdup(value);
	newn->next = NULL;
	if (!*env)
		*env = newn;
	else
		cur->next = newn;
	return (0);
}

/*
** Algoritmo: remove no por chave ajustando ponteiros da lista.
*/
int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prv;

	prv = NULL;
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (!prv)
				*env = cur->next;
			else
				prv->next = cur->next;
			return (free(cur->key), free(cur->value), free(cur), 0);
		}
		prv = cur;
		cur = cur->next;
	}
	return (0);
}

static int	env_count(t_env *e)
{
	int	c;

	c = 0;
	while (e)
	{
		c++;
		e = e->next;
	}
	return (c);
}

/*
** Algoritmo: converte lista para vetor "KEY=VALUE" para execve.
** Ponto de atencao: vetor termina com NULL obrigatoriamente.
*/
char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = ft_strjoin3(env->key, "=", env->value);
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
