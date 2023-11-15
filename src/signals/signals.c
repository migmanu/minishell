/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:11 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/15 17:30:08 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include <signal.h>

// INFO: testing ioctl with TIOCSTI for simulate a new line from user
// a normal \n doesnt work good with here_doc,
// rl_on_new_line and not rl_redisplay, because its not necessary redisplays all
// and it cause a extra space on here_doc
void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
	}
	// (void)signum;
}

void	config_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
