/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtis_router.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/1/13 14:01:08 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/13 17:11:27 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	(*builtins_router(char *str))(t_data *mish, t_scmd cmd)
{
	if (ft_strncmp("echo", str, 4) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("cd", str, 2) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("pwd", str, 3) == 0)
		return (&mish_pwd); // change for pointer
	if (ft_strncmp("export", str, 6) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("unset", str, 5) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("env", str, 3) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("exit", str, 4) == 0)
		return (NULL); // change for pointer
	return (NULL);
}
