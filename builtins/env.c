/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:27:52 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/03 11:46:48 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_cmd(void)
{
	t_env	*env;

	env = g_glob.env;
	while (env)
	{
		if (env->isenv)
		{
			ft_putstr_fd(env->content, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
}
