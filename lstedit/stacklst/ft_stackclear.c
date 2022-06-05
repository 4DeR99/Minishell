/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:16:05 by smazouz           #+#    #+#             */
/*   Updated: 2022/05/24 10:41:34 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void	ft_stackclear(t_stack **lst, void (*del)(void*))
{
	t_stack	*nod;
	t_stack	*temp;

	temp = (*lst);
	while (temp != NULL)
	{
		nod = temp->next;
		ft_stackdelone(temp, del);
		temp = nod;
	}
	*lst = NULL;
}
