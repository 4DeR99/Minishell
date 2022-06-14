/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:46:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/08 19:40:38 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!((arg[i] >= '0' && arg[i] <= '9')
				|| arg[i] == '+' || arg[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(char **args)
{
	if (!args[1])
		exit(g_glob.status);
	if (args[1])
	{
		if (!is_digit(args[1]))
		{
			ft_putstr_fd("Minishell: exit: ", 1);
			ft_putstr_fd(args[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit(255);
		}
		if (!args[2])
			exit(ft_atoi(args[1]));
	}
	g_glob.status = 1;
	ft_putstr_fd("Minishell: exit: too many arguments", 1);
}
