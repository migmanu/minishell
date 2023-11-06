/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/06 13:23:06 by migmanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[])
{
	if (argc != 1)
	{
		printf("minishell takes no arguments, you passed %s\n", argv[1]);
		exit(ERROR);
	}
	init_promt("HOME");
	return (0);
}
