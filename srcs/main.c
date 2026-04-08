/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:20:47 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:21:05 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

/*
** Algoritmo principal do minishell:
** 1) Inicializa ambiente mutavel e sinais interativos.
** 2) Loop: readline -> validacoes -> lexer -> parser -> execucao.
** 3) Atualiza status global de retorno para suportar "$?".
** 4) Sai com Ctrl-D (readline retorna NULL).
** Motivacao: fluxo linear facilita depuracao e garante liberacao de memoria.
*/
static void	process_line(t_shell *sh, char *line)
{
	char	**tk;
	int		n;
	t_cmd	*cmds;

	if (!*line)
		return ;
	add_history(line);
	if (has_unclosed_quotes(line))
		return ((void)printf("minishell: quote nao fechada\n"));
	tk = lex_line(line, sh, &n);
	if (!tk)
		return ;
	cmds = parse_cmds(tk, n);
	free_words(tk);
	exec_line(sh, cmds);
	free_cmds(cmds);
}

static void	shell_loop(t_shell *sh)
{
	char	*line;

	sh->running = 1;
	while (sh->running)
	{
		line = readline("msh$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_line(sh, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	sh.env = env_from_array(envp);
	sh.last_status = 0;
	setup_signals_interactive();
	shell_loop(&sh);
	env_free(sh.env);
	rl_clear_history();
	return (sh.last_status);
}
