/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:47:44 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/08 15:38:33 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	*rest_of_line(char *line)
{
	int		len;
	int		len_;
	char	*rest;

	len = 0;
	len_ = 0;
	rest = malloc(ft_get_line(line) + 2);
	if (!rest)
		return (NULL);
	len = 0;
	while (line[len] != '$' && line[len] != '\0')
	{
		rest[len] = line[len];
		len++;
	}
	len_ = len + 1;
	while (is_alpha_n(line[len_]) == 0 && line[len_])
		len_++;
	while (line[len_])
		rest[len++] = line[len_++];
	rest[len] = '\n';
	rest[len + 1] = '\0';
	return (free(line), rest);
}

static char	*ft_make_new_line(char *line, char *var, int size, int d_r)
{
	int		v_l;
	int		v_l_;
	int		new_var;
	char	*n_l;
	char	*v_n;

	v_n = var_name(line);
	new_var = -1;
	v_l = -1;
	v_l_ = 0;
	n_l = malloc(size + 2);
	if (!n_l)
		return (NULL);
	while (line[++v_l])
	{
		if (line[v_l_] == '$' && d_r == 0)
		{
			d_r++;
			while (var[++new_var])
				n_l[v_l_++] = var[new_var];
			v_l += (ft_strlen(v_n) + 1);
		}
		n_l[v_l_++] = line[v_l];
	}
	return (free(line), free(v_n), n_l[v_l_ - 1] = '\n', n_l[v_l_] = '\0', n_l);
}

static char	*up_line(char *line)
{
	char	*var;
	int		size;
	int		dollar_number;
	char	*v_name;

	dollar_number = 0;
	v_name = var_name(line);
	var = ft_find_path(v_name);
	if (!var)
		return (free(v_name), rest_of_line(line));
	size = (ft_strlen(line) + ft_strlen(var)) - ft_strlen(v_name);
	free(v_name);
	return (ft_make_new_line(line, var, size, dollar_number));
}

static int	check_for_dollar(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = 0;
	while (line[len])
	{
		if (line[len] == '$')
			return (-1);
		len++;
	}
	return (len);
}

int	read_from_here_doc(int fd_in, char *limiter)
{
	char	*line;

	line = ft_read();
	if (!line)
		return (0);
	while (ft_strcmp(line, limiter) != 10)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			return (0);
		}
		while (check_for_dollar(line) == -1)
			line = up_line(line);
		ft_putstr_fd(line, fd_in);
		free(line);
		line = ft_read();
	}
	free(line);
	return (1);
}
