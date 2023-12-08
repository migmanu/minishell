/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:11 by migmanu           #+#    #+#             */
/*   Updated: 2023/12/08 14:32:52 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// #include <asm-generic/ioctls.h>

static void	handle_sigint_input(int signum)
{
	g_signal = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigint_exec(int signum)
{
	g_signal = signum;
	write(1, "\n", 1);
}

void	config_signals_input(void)
{
	signal(SIGINT, handle_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}

void	config_signals_exec(void)
{
	signal(SIGINT, handle_sigint_exec);
	signal(SIGQUIT, SIG_IGN);
}
