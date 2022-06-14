/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_rf_quotes__.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:23:54 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:52:36 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*var_name_util(char *line, int len, int size)
{
	char	*var;
	int		x;

	x = 0;
	var = malloc(size + 1);
	if (!var)
		return (NULL);
	while (is_alpha_n(line[len]) == 0 && line[len])
		var[x++] = line[len++];
	var[x] = '\0';
	return (var);
}

char	*variable_name(char *line)
{
	int		len;
	char	*var;
	int		x;

	x = 0;
	len = 0;
	while (line[x] != '$' && line[x])
	{
		if (line[x] == '\'')
		{
			x++;
			while (line[x] != '\'')
				x++;
		}
		x++;
	}
	len = x + 1;
	if (line[len] == '?')
		return (ft_strdup("?"));
	while (is_alpha_n(line[len]) == 0 && line[len])
		len++;
	var = var_name_util(line, x + 1, len - x);
	return (var);
}
