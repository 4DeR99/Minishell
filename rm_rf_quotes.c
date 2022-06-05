/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_rf_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:31:43 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/02 10:18:07 by moulmado         ###   ########.fr       */
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

static char	*variable_name(char *line)
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
	while (is_alpha_n(line[len]) == 0 && line[len])
		len++;
	var = var_name_util(line, x + 1, len - x);
	return (var);
}

static char	*rest_of_line(char *line, int *dollar_index)
{
	int		len;
	int		len_;
	char	*rest;

	len = 0;
	len_ = 0;
	rest = malloc(ft_get_line(line) + 1);
	if (!rest)
		return (NULL);
	len = 0;
	while (len != *dollar_index && line[len])
	{
		rest[len] = line[len];
		len++;
	}
	len_ = len + 1;
	while (is_alpha_n(line[len_]) == 0 && line[len_])
		len_++;
	while (line[len_])
		rest[len++] = line[len_++];
	rest[len] = '\0';
	// free(line);
	return (rest);
}

static char	*make_new_line(char *line, char *var, int size, int *dollar_index)
{
	int		var_len;
	int		var_len_;
	int		new_var;
	char	*new_line;

	new_var = 0;
	var_len = 0;
	var_len_ = 0;
	new_line = malloc(size + 1);
	if (!new_line)
		return (NULL);
	while (line[var_len])
	{
		if (var_len == *dollar_index)
		{
			while (var[new_var])
				new_line[var_len_++] = var[new_var++];
			var_len += (ft_strlen(variable_name(line)) + 1);
		}
		new_line[var_len_++] = line[var_len++];
	}
	new_line[var_len_] = '\0';
	return (new_line);
}

static char	*up_line(char *line, int *dollar_index)
{
	char	*var;
	int		size;
	char	*v_name;
	char	*re;

	size = 0;
	v_name = variable_name(line);
	var = getenv(v_name);
	if (!var)
		return (free(v_name), rest_of_line(line, dollar_index));
	// var = join_2(join_2(ft_strdup("|"), var), "|");
	size = ft_strlen(line) + ft_strlen(var) - ft_strlen(v_name);
	free(v_name);
	re = make_new_line(line, var, size, dollar_index);
	// free(line);
	return (re);
}

static int	check_for_dollar(char *line, int *dollar_index)
{
	int	len;
	int	double_q;

	if (!line)
		return (0);
	len = 0;
	double_q = 0;
	while (line[len])
	{
		if (line[len] == '"')
			double_q++;
		if (line[len] == '\'' && double_q % 2 == 0)
		{
			len++;
			while (line[len] != '\'')
				len++;
		}
		if (line[len] == '$')
		{
			*dollar_index = len;
			return (-1);
		}
		len++;
	}
	return (0);
}

char	*expand_var(char *str)
{
	int	dollar_index;

	dollar_index = -1;
	while (check_for_dollar(str, &dollar_index))
		str = up_line(str, &dollar_index);
	return (str);
}
