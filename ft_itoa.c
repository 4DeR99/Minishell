/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:54:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:55:14 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	num_len(long n)
{
	int	l;

	l = 0;
	if (n == 0)
		l = 1;
	if (n < 0)
	{
		l++;
		n *= -1;
	}
	while (n > 0)
	{
		l++;
		n /= 10;
	}
	return (l);
}

static int	power_of_ten(int n)
{
	int	pot;

	pot = 1;
	if (!n)
		return (pot);
	while (n > 0)
	{	
		pot *= 10;
		n--;
	}
	return (pot);
}

char	*ft_itoa(int nbr)
{
	char	*re;
	int		n_l;
	int		i;
	long	n;

	n = nbr;
	n_l = num_len(n);
	re = malloc((n_l + 1) * sizeof(char));
	if (!re)
		return (0);
	i = 0;
	if (n < 0)
	{
		re[i++] = '-';
		n_l--;
		n *= -1;
	}
	n_l--;
	while (n_l >= 0)
	{
		re[i++] = ((n / power_of_ten(n_l)) % 10) + '0';
		n_l--;
	}
	re[i] = '\0';
	return (re);
}
