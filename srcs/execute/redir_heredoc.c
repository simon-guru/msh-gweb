/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:30:43 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:30:56 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

char	*expand_name(const char *s, int *i, t_shell *sh);

static char	*expand_heredoc_line(const char *line, t_shell *sh)
{
	char	*out;
	int		i;
	int		j;

	out = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			j = i + 1;
			if (line[j] == '?' || ft_isalnum(line[j]))
			{
				out = ft_strjoin3(out, expand_name(line, &j, sh), "");
				i = j;
			}
			else
			{
				out = ft_strjoin3(out, ft_substr(line, i, 1), "");
				i++;
			}
		}
		else
		{
			out = ft_strjoin3(out, ft_substr(line, i, 1), "");
			i++;
		}
	}
	return (out);
}

static int	handle_heredoc(char *lim, t_shell *sh)
{
	int		fd[2];
	char	*line;
	char	*expanded;

	if (pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || g_sig == SIGINT || !ft_strcmp(line, lim))
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, sh);
		write(fd[1], expanded, ft_strlen(expanded));
		write(fd[1], "\n", 1);
		free(expanded);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	apply_redirs(t_redir *r, t_shell *sh)
{
	int	fd;

	while (r)
	{
		if (r->type == 1)
			fd = open(r->target, O_RDONLY);
		else if (r->type == 2)
			fd = open(r->target, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (r->type == 4)
			fd = open(r->target, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = handle_heredoc(r->target, sh);
		if (fd < 0)
			return (perror(r->target), 1);
		if (r->type == 1 || r->type == 3)
			dup2(fd, 0);
		else
			dup2(fd, 1);
		close(fd);
		r = r->next;
	}
	return (0);
}
