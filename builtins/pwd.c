/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:46:26 by moulmado          #+#    #+#             */
/*   Updated: 2022/05/21 23:52:49 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(void)
{
	char	path[1024];

	getcwd(path, 1024);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
}