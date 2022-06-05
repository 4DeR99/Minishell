/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:14:44 by smazouz           #+#    #+#             */
/*   Updated: 2022/04/15 03:09:23 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t destsize, int start)
{
	size_t			i;
	size_t			j;
	unsigned int	l;

	i = start;
	j = 0;
	l = 0;
	while (src[l] != '\0')
		l++;
	if (destsize == 0)
		return (l);
	while (src[j] != '\0' && j < (destsize - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (l);
}
