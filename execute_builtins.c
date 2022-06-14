/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:48:29 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/09 09:06:50 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
		i++;
	}
}

int	execute_builtins(char **args, int ou)
{
	to_lower(args[0]);
	if (!ft_strcmp(args[0], "echo"))
		echo_cmd(args, ou);
	else if (!ft_strcmp(args[0], "cd"))
		cd_cmd(args);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd_cmd(ou);
	else if (!ft_strcmp(args[0], "exit"))
		exit_cmd(args);
	else if (!ft_strcmp(args[0], "env"))
		env_cmd();
	else if (!ft_strcmp(args[0], "export"))
		export_cmd(args);
	else if (!ft_strcmp(args[0], "unset"))
		unset_cmd(args);
	else
		return (0);
	return (1);
}
