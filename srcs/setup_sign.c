/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smayunga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 22:21:19 by smayunga          #+#    #+#             */
/*   Updated: 2026/03/03 22:21:34 by smayunga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mshell.h"
#include "utils.h"

volatile sig_atomic_t	g_sig = 0;

static void	h_sigint(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals_interactive(void)
{
	signal(SIGINT, h_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
