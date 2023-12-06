/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:11 by migmanu           #+#    #+#             */
/*   Updated: 2023/12/06 18:35:56 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>

static void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 128 + signum;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_sigint_ln(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 128 + signum;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	config_signals(t_data *mish)
{
	if (mish->in_cmd == 1)
	{
		signal(SIGINT, handle_sigint_ln);
	}
	else if (mish->in_cmd == 0)
	{
		signal(SIGINT, handle_sigint);
	}
	else
	{
		signal(SIGINT, handle_sigint);
	}
	signal(SIGQUIT, SIG_IGN);
}
