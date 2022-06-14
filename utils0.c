/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:27:42 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/08 19:42:44 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	cnt;

	cnt = 0;
	while (n)
	{
		if (!s1[cnt] || !s2[cnt] || s1[cnt] != s2[cnt])
			return ((unsigned char)s1[cnt] - (unsigned char)s2[cnt]);
		cnt++;
		n--;
	}
	return (0);
}

int	lst_size(char **lst)
{
	int	size;

	size = 0;
	while (lst[size])
		size++;
	return (size);
}

char	*join_2(char *s0, char *s1)
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
	re = (char *)malloc(s0_len + s1_len + 1);
	if (!re)
		return (0);
	c0 = -1;
	c1 = 0;
	while (++c0 < s0_len)
		re[c0] = s0[c0];
	c1 = 0;
	while (c1 < s1_len)
		re[c0++] = s1[c1++];
	re[c0] = '\0';
	return (free(s0), re);
}

int	ft_atoi(const char *s)
{
	int		nbr;
	int		n;
	int		i;

	n = 1;
	nbr = 0;
	i = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r' || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			n *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr = (nbr * 10) + (s[i] - '0');
		i++;
	}
	return (nbr * n);
}
