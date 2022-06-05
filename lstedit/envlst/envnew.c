/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:27:23 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/03 11:57:21 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*envnew(char *content, int isenv, int isprinted)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->content = content;
	env->next = NULL;
	env->previous = NULL;
	env->isenv = isenv;
	env->isprinted = isprinted;
	return (env);
}
