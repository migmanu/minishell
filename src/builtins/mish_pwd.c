/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:25:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/06 13:09:07 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Imitates Bash's pwd function. If if_exit set to IS_EXIT (1),
// mish_cd will kill current process. NOT_EXIT used for when
// only one builtin command inputed
void	mish_pwd(t_data *mish, t_scmd cmd, int if_exit)
{
	char	*str;

	str = hashmap_search(mish->env, "PWD");
	if (str == NULL)
	{
		handle_exit(mish, NULL, FAILURE, if_exit);
		return ;
	}
	ft_putstr_fd(str, cmd.out_fd);
	ft_putstr_fd("\n", cmd.out_fd);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
