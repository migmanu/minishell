/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtis_router.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:01:08 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/13 14:27:27 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	(*builtins_router(t_data *mish, t_scmd cmd))(t_data *mish, t_scmd cmd)
{
	static char	*keys[7] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};

	if (ft_strncmp("echo", cmd.full_cmd[1], 4) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("cd", cmd.full_cmd[1], 2) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("pwd", cmd.full_cmd[1], 3) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("export", cmd.full_cmd[1], 6) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("unset", cmd.full_cmd[1], 5) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("env", cmd.full_cmd[1], 3) == 0)
		return (NULL); // change for pointer
	if (ft_strncmp("exit", cmd.full_cmd[1], 4) == 0)
		return (NULL); // change for pointer
	return (NULL);
}
