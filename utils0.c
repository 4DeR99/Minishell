/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 22:27:42 by moulmado          #+#    #+#             */
/*   Updated: 2022/05/31 19:05:50 by moulmado         ###   ########.fr       */
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

	size =0;
	while (lst[size])
		size++;
	return (size);
}

void	color(int c_nb)
{
	if (c_nb == RED)
		write(1, "\033[0;31m", slen("\033[0;31m"));
	if (c_nb == BLUE)
		write(1, "\033[0;34m", slen("\033[0;34m"));
	if (c_nb == CYAN)
		write(1, "\033[1;36m", slen("\033[0;36m"));
	if (c_nb == YELLOW)
		write(1, "\033[0;33m", slen("\033[0;33m"));
	if (c_nb == WHITE)
		write(1, "\033[0;37m", slen("\033[0;37m"));
	if (c_nb == GREEN)
		write(1, "\033[0;32m", slen("\033[0;32m"));
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
	{
		ft_putstr_fd("hi\n",1);
		return (0);
	}
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
