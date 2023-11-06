/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:22:11 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/06 17:51:58 by migmanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include <signal.h>

void	handle_sigint()
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof()
{
	printf("eof\n");
	exit(SUCCESS);
}

void	sig_listener()
{
	int i;

	i = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, handle_eof);
}
