/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:30:00 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:30:15 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

static int	is_redir(const char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, "<<") || !ft_strcmp(s, ">>"));
}

static int	redir_type(const char *s)
{
	if (!ft_strcmp(s, "<"))
		return (1);
	if (!ft_strcmp(s, ">"))
		return (2);
	if (!ft_strcmp(s, "<<"))
		return (3);
	return (4);
}

static void	redir_add(t_redir **lst, const char *op, const char *tg)
{
	t_redir	*n;
	t_redir	*c;

	n = malloc(sizeof(t_redir));
	if (!n)
		return ;
	n->type = redir_type(op);
	n->target = ft_strdup(tg);
	n->next = NULL;
	if (!*lst)
		*lst = n;
	else
	{
		c = *lst;
		while (c->next)
			c = c->next;
		c->next = n;
	}
}

static int	count_args(char **tk, int i)
{
	int	count;

	count = 0;
	while (tk[i] && ft_strcmp(tk[i], "|"))
	{
		if (is_redir(tk[i]))
		{
			if (tk[i + 1])
				i += 2;
			else
				i += 1;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static t_cmd	*parse_one(char **tk, int *i)
{
	t_cmd	*c;
	int		k;
	int		argc;

	c = malloc(sizeof(t_cmd));
	if (!c)
		return (NULL);
	argc = count_args(tk, *i);
	c->argv = malloc(sizeof(char *) * (argc + 1));
	c->redirs = NULL;
	c->next = NULL;
	if (!c->argv)
		return (free(c), NULL);
	k = 0;
	while (tk[*i] && ft_strcmp(tk[*i], "|"))
	{
		if (is_redir(tk[*i]))
		{
			if (!tk[*i + 1])
			{
				printf("msh: syntax error near '%s'\n", tk[*i]);
				free_cmds(c);
				return (NULL);
			}
			redir_add(&c->redirs, tk[*i], tk[*i + 1]);
			*i += 2;
		}
		else
			c->argv[k++] = ft_strdup(tk[(*i)++]);
	}
	c->argv[k] = NULL;
	if (tk[*i] && !ft_strcmp(tk[*i], "|"))
		(*i)++;
	return (c);
}

t_cmd	*parse_cmds(char **tk, int n)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*node;
	int		i;

	(void)n;
	head = NULL;
	tail = NULL;
	i = 0;
	while (tk[i])
	{
		node = parse_one(tk, &i);
		if (!node)
			return (free_cmds(head), NULL);
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
