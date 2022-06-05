/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:45:16 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/03 12:41:56 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	n_flag(char **args)
{
	int	index;

	index = 0;
	if (args[1][index++] == '-')
	{
		while (args[1][index] == 'n')
		{
			if (args[1][index + 1] == '\0')
				return (2);
			index++;
		}
	}
	return (1);
}

static void	execute_echo(char **args, int index)
{
	while (args[index])
	{
		ft_putstr_fd(args[index++], 1);
		if (args[index])
			ft_putchar_fd(' ', 1);
	}
}

void	echo_cmd(char **args)
{
	int	n;
	int	index;

	index = 0;
	n = n_flag(args);
	execute_echo(args, n);
	if (n == 2)
		ft_putchar_fd('\n', 1);
}
