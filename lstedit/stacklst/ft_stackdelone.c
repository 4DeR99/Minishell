/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:19:57 by smazouz           #+#    #+#             */
/*   Updated: 2022/05/24 10:41:39 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	ft_stackdelone(t_stack *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->op);
	free(lst);
}
