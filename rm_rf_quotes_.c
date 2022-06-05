/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_rf_quotes_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:07:49 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/03 10:25:14 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_count(char *str, char c)
{
	int	quotes;
	int	index;

	index = 0;
	quotes = 0;
	while (str[index])
	{
		if (str[index] == c)
			quotes++;
		index++;
	}
	return (quotes);
}

static char	*quotes_remove(char *str, char c)
{
	char	*re;
	int		index;
	int		size;
	int		x;

	index = 0;
	x = 0;
	size = slen(str) - quotes_count(str, c);
	re = malloc(size + 1);
	if (!re)
		return (NULL);
	while (index < size)
	{
		if (str[x] != c)
			re[index++] = str[x];
		x++;
	}
	re[index] = '\0';
	return (free(str), re);
}

char	*rm_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (quotes_remove(str, '\''));
		if (str[i] == '"')
			return (quotes_remove(str, '"'));
		i++;
	}
	return (str);
}
