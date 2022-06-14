/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:27:52 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/08 16:13:04 by smazouz          ###   ########.fr       */
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
