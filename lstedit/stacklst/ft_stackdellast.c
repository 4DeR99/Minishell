/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackdellast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:34:46 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/04 13:31:24 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_stackdellast(t_stack **stack)
{
	t_stack	*tmp;

	if (!ft_stacklast(*stack)->prev)
	{
		free((*stack)->op);
		free(*stack);
		*stack = NULL;
		return ;
	}
	tmp = ft_stacklast(*stack)->prev;
	free(ft_stacklast(*stack)->op);
	free(ft_stacklast(*stack));
	tmp->next = NULL;
}
