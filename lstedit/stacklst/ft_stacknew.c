/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacknew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:25:02 by smazouz           #+#    #+#             */
/*   Updated: 2022/05/24 10:41:47 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

t_stack	*ft_stacknew(char *op, int prio)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->prio = prio;
	stack->op = op;
	stack->prev = NULL;
	stack->next = NULL;
	return (stack);
}
