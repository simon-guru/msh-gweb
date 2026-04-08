/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeme.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:29:32 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:29:50 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

char	*expand_name(const char *s, int *i, t_shell *sh);

static int	is_meta(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static char	*append_piece(char *acc, char *piece)
{
	char	*tmp;

	tmp = ft_strjoin3(acc, piece, "");
	free(acc);
	free(piece);
	return (tmp);
}

static char	*read_word(const char *s, int *i, t_shell *sh)
{
	char	q;
	char	*out;
	int		j;

	out = ft_strdup("");
	q = 0;
	while (s[*i] && (q || (!is_meta(s[*i]) && s[*i] != ' ' && s[*i] != '\t')))
	{
		if (!q && (s[*i] == '\'' || s[*i] == '"'))
			q = s[(*i)++];
		else if (q && s[*i] == q)
		{
			q = 0;
			(*i)++;
		}
		else if (s[*i] == '$' && q != '\'')
		{
			j = *i + 1;
			if (s[j] == '?' || ft_isalnum(s[j]))
			{
				out = append_piece(out, expand_name(s, &j, sh));
				*i = j;
			}
			else
				out = append_piece(out, ft_substr(s, (*i)++, 1));
		}
		else
			out = append_piece(out, ft_substr(s, (*i)++, 1));
	}
	return (out);
}

static char	*read_meta(const char *line, int *i)
{
	int	len;

	len = 1;
	if (line[*i] && line[*i] == line[*i + 1]
		&& (line[*i] == '<' || line[*i] == '>'))
		len = 2;
	return ((*i += len), ft_substr(line, *i - len, len));
}

char	**lex_line(const char *line, t_shell *sh, int *tokc)
{
	char	**tk;
	int		i;
	int		k;

	tk = malloc(sizeof(char *) * (ft_strlen(line) * 2 + 2));
	if (!tk)
		return (NULL);
	i = 0;
	k = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!line[i])
			break ;
		if (is_meta(line[i]))
			tk[k++] = read_meta(line, &i);
		else
			tk[k++] = read_word(line, &i, sh);
	}
	tk[k] = NULL;
	*tokc = k;
	return (tk);
}

int	has_unclosed_quotes(const char *s)
{
	char	q;
	int		i;

	q = 0;
	i = 0;
	while (s[i])
	{
		if (!q && (s[i] == '\'' || s[i] == '"'))
			q = s[i];
		else if (q && s[i] == q)
			q = 0;
		i++;
	}
	return (q != 0);
}
