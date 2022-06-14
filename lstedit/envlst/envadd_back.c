/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:33:26 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:46:31 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	envadd_back(t_env *env, t_env *new)
{
	t_env	*node;

	if (env == NULL)
		env = new;
	else
	{
		node = envlast(env);
		node->next = new;
		new->previous = node;
	}
}
