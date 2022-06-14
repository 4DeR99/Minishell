/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_nd_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:07:20 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/07 06:18:46 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tab_allocation_size(char *args, int index, int size)
{
	while (args[index])
	{
		if (args[index] == ' ')
		{
			size++;
			while (args[index] == ' ' && args[index])
				index++;
		}
		if (args[index] == '"')
		{
			index++;
			while (args[index] != '"')
				index++;
		}
		if (args[index] == '\'')
		{
			index++;
			while (args[index] != '\'')
				index++;
		}
		index++;
	}
	size++;
	return (size);
}

static int	str_allocation_size(char *args, int i)
{
	int	tmp;

	tmp = i;
	while (args[i] && args[i] != ' ' && args)
	{
		if (args[i] == '"')
		{
			i++;
			while (args[i] != '"')
				i++;
		}
		else if (args[i] == '\'')
		{
			i++;
			while (args[i] != '\'')
				i++;
		}
		i++;
	}
	return (i - tmp);
}

static void	quotes_condition(char *args, char *re, int *index, int *i)
{
	if (args[*index] == '"')
	{
		re[*i] = args[*index];
		*i += 1;
		*index += 1;
		while (args[*index] != '"')
		{
			re[*i] = args[*index];
			*i += 1;
			*index += 1;
		}
	}
	if (args[*index] == '\'')
	{
		re[*i] = args[*index];
		*i += 1;
		*index += 1;
		while (args[*index] != '\'')
		{
			re[*i] = args[*index];
			*i += 1;
			*index += 1;
		}
	}
}

static char	*split_args(char *args, int i)
{
	char		*re;
	static int	index;

	if (!args)
	{
		index = 0;
		return (0);
	}
	re = malloc(str_allocation_size(args, index) + 1);
	if (!re)
		return (NULL);
	while (args[index] && args[index] != ' ')
	{
		quotes_condition(args, re, &index, &i);
		re[i++] = args[index++];
	}
	re[i] = '\0';
	while (args[index] && args[index] == ' ')
		index++;
	return (re);
}

char	**split_cmd_nd_args(char *args)
{
	char	**re;
	int		size;
	int		index;
	char	*tmp;

	tmp = args;
	index = 0;
	args = expand_var(args);
	size = tab_allocation_size(args, 0, 0);
	re = malloc(sizeof(char *) * (size + 1));
	if (!re)
		return (NULL);
	while (index < size)
		re[index++] = rm_quotes(split_args(args, 0));
	re[index] = NULL;
	split_args(NULL, 0);
	if (tmp != args)
		free(args);
	return (re);
}
