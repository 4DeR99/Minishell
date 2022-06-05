/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:18:52 by moulmado          #+#    #+#             */
/*   Updated: 2022/05/30 14:19:00 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s0, char *s1)
{
	int		c0;
	int		c1;
	int		s0_len;
	int		s1_len;
	char	*re;

	if (!s0)
		s0 = ft_strdup("");
	s0_len = slen(s0);
	s1_len = slen(s1);
	re = (char *)malloc(s0_len + s1_len + 2);
	if (!re)
		return (0);
	c0 = -1;
	c1 = 0;
	while (++c0 < s0_len)
		re[c0] = s0[c0];
	c1 = 0;
	re[c0++] = ',';
	while (c1 < s1_len)
		re[c0++] = s1[c1++];
	re[c0] = '\0';
	return (free(s0), re);
}

int	slen(char *c)
{
	int	l;

	if (!c)
		return (0);
	l = 0;
	while (c[l])
		l++;
	return (l);
}

int	ft_strchr(char *str, int c)
{
	int		index;
	char	c1;
	char	*str1;

	if (!str)
		return (1);
	str1 = (char *)str;
	index = 0;
	c1 = (char)c;
	while (str1[index] != c1 && str1[index])
		index++;
	if (str1[index] == c1)
		return (0);
	return (1);
}

char	*ft_strdup(char *s)
{
	char	*re;
	int		len;
	int		i;

	len = slen(s);
	re = (char *)malloc(len + 1);
	if (!re)
		return (0);
	i = 0;
	while (s[i])
	{
		re[i] = s[i];
		i++;
	}
	re[i] = '\0';
	return (re);
}

void	error_msg(char *error)
{
	color(RED);
	write(2, "Error:\n", slen("error:\n"));
	color(WHITE);
	write(2, error, slen(error));
}