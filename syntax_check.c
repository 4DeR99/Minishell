/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:23:03 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:35:35 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	op_at_beg(char *input)
{
	int	index;

	index = 0;
	while (input[index] == ' ')
		index++;
	if (input[index] == '&' || input[index] == '|'
		|| input[index] == '>' || input[index] == '<')
		return (1);
	return (0);
}

static int	op_at_end(char *input)
{
	int	index;

	index = slen(input) - 1;
	while (input[index] == ' ')
		index--;
	if (input[index] == '&' || input[index] == '|' || input[index] == '>'
		|| input[index] == '<')
		return (1);
	return (0);
}

static int	pipe_nd_openparenth(char *input, int *index)
{
	*index += 1;
	if (input[*index] == '&' || input[*index] == '|'
		|| input[*index] == ')')
		return (1);
	while (input[*index] == ' ')
		*index += 1;
	if (input[*index] == '&' || input[*index] == '|'
		|| input[*index] == ')')
		return (1);
	return (0);
}

static int	double_op(char *input, int index)
{
	while (input[index])
	{
		if ((input[index] == '|' && input[index + 1] == '|')
			|| (input[index] == '&' && input[index + 1] == '&'))
		{
			index += 2;
			if (input[index] == '&' || input[index] == '|'
				|| input[index] == ')' || input[index] == '>'
				|| input[index] == '<')
				return (1);
			while (input[index] == ' ')
				index += 1;
			if (input[index] == '&' || input[index] == '|'
				|| input[index] == ')' || input[index] == '>'
				|| input[index] == '<')
				return (1);
		}
		else if (input[index] == '|' || input[index] == '('
			|| input[index] == '<' || input[index] == '>')
			if (pipe_nd_openparenth(input, &index))
				return (1);
		index++;
	}
	return (0);
}

int	check_syntax(char *input)
{
	if (op_at_beg(input) || op_at_end(input) || double_op(input, 0))
	{
		ft_putstr_fd("Minishell : syntax error\n", 2);
		g_glob.status = 258;
		return (1);
	}
	return (0);
}
