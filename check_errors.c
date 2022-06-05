/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:13:52 by moulmado          #+#    #+#             */
/*   Updated: 2022/05/24 11:04:47 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_4_quotes(char *input, int *double_q, int *single_q)
{
	int index;

	index = 0;
	while (input[index])
	{
		if (input[index] == '"')
		{
			*double_q = 1;
			index++;
			while (input[index] != '"' && input[index])
				index++;
			if (input[index] == '"')
				*double_q = 0;
		}
		else if (input[index] == '\'')
		{
			*single_q = 1;
			index++;
			while (input[index] != '\'' && input[index])
				index++;
			if (input[index] == '\'')
				*single_q = 0;
		}
		index++;
	}
}

static int	parenthesses_error(int prentheses)
{
	if (prentheses > 0)
	{
		error_msg("expected this \")\" to match this \"(\"\n");
		return (1);
	}
	if (prentheses < 0)
	{
		error_msg("expected this \"(\" before this \")\"\n");
		return (1);
	}
	return (0);
}

int	check_4_parentheses(char *input)
{
	int	prentheses;
	int	index;

	prentheses = 0;
	index = 0;
	while (input[index])
	{
		if (input[index] == '(')
			prentheses++;
		if (input[index] == ')')
		{
			if (prentheses == 0)
			{
				prentheses--;
				break ;
			}
			prentheses--;
		}
		index++;
	}
	if (parenthesses_error(prentheses))
		return (1);
	return (0);
}

int	check_4_quotes(char *input)
{
	int	double_q;
	int	single_q;

	double_q = 0;
	single_q = 0;
	loop_4_quotes(input, &double_q, &single_q);
	if (single_q || double_q)
	{
		ft_putstr_fd("Minishell : syntax error\n", 2);
		return (1);
	}
	return (0);
}
