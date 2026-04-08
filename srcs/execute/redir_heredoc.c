/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:30:43 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/16 15:00:00 by smayunga         ###   ########.fr       */
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
	char	*expanded;
	char	*tmp;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			j = i + 1;
			if (line[j] == '?' || ft_isalnum(line[j]))
			{
				expanded = expand_name(line, &j, sh);
				tmp = ft_strjoin3(out, expanded, "");
				free(out);
				free(expanded);
				out = tmp;
				i = j;
			}
			else
			{
				tmp = ft_strjoin3(out, "$", "");
				free(out);
				out = tmp;
				i++;
			}
		}
		else
		{
			tmp = ft_strjoin3(out, ft_substr(line, i, 1), "");
			free(out);
			out = tmp;
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
	int		len;

	if (pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd[1]);
			close(fd[0]);
			return (-1);
		}
		if (g_sig == SIGINT)
		{
			free(line);
			close(fd[1]);
			close(fd[0]);
			g_sig = 0;
			return (-1);
		}
		if (!ft_strcmp(line, lim))
		{
			free(line);
			break ;
		}
		expanded = expand_heredoc_line(line, sh);
		if (expanded)
		{
			len = ft_strlen(expanded);
			write(fd[1], expanded, len);
			write(fd[1], "\n", 1);
			free(expanded);
		}
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

int	apply_redirs(t_redir *r, t_shell *sh)
{
	int	fd_in;
	int	fd_out;

	fd_in = -1;
	fd_out = -1;
	while (r)
	{
		if (r->type == 1)
		{
			if (fd_in >= 0)
				close(fd_in);
			fd_in = open(r->target, O_RDONLY);
			if (fd_in < 0)
				return (perror(r->target), 1);
		}
		else if (r->type == 2)
		{
			if (fd_out >= 0)
				close(fd_out);
			fd_out = open(r->target, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd_out < 0)
				return (perror(r->target), 1);
		}
		else if (r->type == 4)
		{
			if (fd_out >= 0)
				close(fd_out);
			fd_out = open(r->target, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd_out < 0)
				return (perror(r->target), 1);
		}
		else if (r->type == 3)
		{
			if (fd_in >= 0)
				close(fd_in);
			fd_in = handle_heredoc(r->target, sh);
			if (fd_in < 0)
				return (1);
		}
		r = r->next;
	}
	if (fd_in >= 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out >= 0)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	return (0);
}
