/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:25:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/13 13:55:39 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_pwd(t_data *mish, t_scmd cmd)
{
	char	*str;

	str = hashmap_search(mish->env, "pwd");
	ft_putstr_fd(str, cmd.out_fd);
}
