/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postfix_expression.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:45:32 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/04 13:34:26 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_prio(char *line , int len, int yes)
{
	if (yes == 1 && line[len] == '|')
		return (2);
	if (yes == 1 && (line[len] == '>' || line[len] == '<'))
		return (3);
	if (yes == 2 && (line[len] == '|' || line[len] == '&'))
		return (0);
	if ((line[len] == '>' || line[len] == '<') && yes == 2)
		return (3);
	if (line[len] == '(')
		return (1);
	if (line[len] == ')')
		return (999);
	return (0);
}

static char	*last_command(char *line, t_stack **stack, t_int *ints)
{
	char	*str;

	str = NULL;
	str = ft_strjoin(str, ft_substr(line, ints->tmp, (ints->len - ints->tmp)));
	while (ft_stacklast(*stack))
	{
		str = ft_strjoin(str, ft_stacklast(*stack)->op);
		ft_stackdellast(stack);
	}
	return (str);
}

static char	*get_op_nd_cmd(char *line, t_stack **stack, t_int *ints, int yes)
{
	int			prio;
	char		*str;

	str = NULL;
	if (yes == EXODIA)
		return (last_command(line, stack, ints));
	prio = get_prio(line, ints->len, yes);
	str = ft_strjoin(str,ft_substr(line, ints->tmp, (ints->len - ints->tmp)));
	if (!ft_stacksize(*stack))
		*stack = ft_stacknew(ft_substr(line, ints->len, yes), prio);
	else
	{
		if (prio == 999)
		{
			while (ft_stacklast(*stack)->prio != 1)
			{
				str = ft_strjoin(str, ft_stacklast(*stack)->op);
				ft_stackdellast(stack);
			}
			ft_stackdellast(stack);
		}
		else if (ft_stacklast(*stack)->op[0] == '(')
			ft_stackadd_back(stack,
				ft_stacknew(ft_substr(line, ints->len, yes), prio));
		else if (ft_stacklast(*stack)->prio < prio)
			ft_stackadd_back(stack,
				ft_stacknew(ft_substr(line, ints->len, yes), prio));
		else
		{
			str = ft_strjoin(str, ft_stacklast(*stack)->op);
			ft_stackdellast(stack);
			ft_stackadd_back(stack,
				ft_stacknew(ft_substr(line, ints->len, yes), prio));
		}
	}
	ints->tmp = ints->len + yes;
	ints->len += yes;
	return (str);
}

char	*postfix_expression(char *line)
{
	t_int	ints;
	t_stack	*stack;
	char	*poxfix;

	poxfix = NULL;
	stack = NULL;
	ints.len = 0;
	ints.tmp = 0;
	while (line[ints.len])
	{
		if (line[ints.len] == '"' || line[ints.len] == '\'')
		{
			ints.len++;
			while (line[ints.len] != '"' && line[ints.len] != '\'')
				ints.len++;
			ints.len++;
		}
		else if (line[ints.len] == '|' && line[ints.len + 1] == '|')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 2));
		else if (line[ints.len] == '&' && line[ints.len + 1] == '&')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 2));
		else if (line[ints.len] == '|' && line[ints.len + 1] != '|')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 1));
		else if (line[ints.len] == '>' && line[ints.len + 1] == '>')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 2));
		else if (line[ints.len] == '<' && line[ints.len + 1] == '<')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 2));
		else if (line[ints.len] == '<' && line[ints.len + 1] != '<')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 1));
		else if (line[ints.len] == '>' && line[ints.len + 1] != '>')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 1));
		else if (line[ints.len] == '(')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 1));
		else if (line[ints.len] == ')')
			poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 1));
		else
			ints.len++;
	}
	poxfix = ft_strjoin(poxfix, get_op_nd_cmd(line, &stack, &ints, 666));
	return (poxfix);
}
