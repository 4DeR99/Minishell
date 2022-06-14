/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postfix_expression_.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:21:17 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 10:02:59 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*postfix_handl(char *line, char *poxfix,
		t_stack **stack, t_int *ints)
{
	if ((line[ints->len] == '|' && line[ints->len + 1] == '|')
		|| (line[ints->len] == '&' && line[ints->len + 1] == '&')
		|| (line[ints->len] == '>' && line[ints->len + 1] == '>')
		|| (line[ints->len] == '<' && line[ints->len + 1] == '<'))
		poxfix = join_ndfree(poxfix, get_op_nd_cmd(line, stack, ints, 2));
	else if ((line[ints->len] == '|' && line[ints->len + 1] != '|')
		|| (line[ints->len] == '<' && line[ints->len + 1] != '<')
		|| (line[ints->len] == '>' && line[ints->len + 1] != '>')
		|| (line[ints->len] == '(' || line[ints->len] == ')'))
		poxfix = join_ndfree(poxfix, get_op_nd_cmd(line, stack, ints, 1));
	else
		ints->len++;
	return (poxfix);
}
