/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:12:11 by smazouz           #+#    #+#             */
/*   Updated: 2022/05/24 10:41:31 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	ft_stackadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*node;

	if (*lst == NULL)
		*lst = new;
	else
	{
		node = ft_stacklast(*lst);
		node->next = new;
		new->prev = node;
	}
}
