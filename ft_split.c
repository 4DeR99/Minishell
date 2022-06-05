/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:34:15 by smazouz           #+#    #+#             */
/*   Updated: 2022/05/23 19:49:40 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	**free_tab(char	**tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab[x]);
	return (NULL);
}

static char	*get_next_word(char *s, char c, int *len)
{
	int				x;
	unsigned int	y;
	unsigned int	start;

	x = 0;
	y = 0;
	start = *len;
	while (s[start] == c)
		start++;
	while (s[x + start] != '\0' && s[x + start] != c)
		x++;
	*len = x;
	return (s + start);
}

static int	ft_word_count(const char *str, char c)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	if (str[x] == c && c != '\0')
		x++;
	while (str[x])
	{
		if (str[x] == c)
		{
			if (str[x - 1] != c)
				y++;
		}
		x++;
	}
	if (str[x - 1] != c && str[x - 1] != '\0')
		y++;
	return (y);
}

static char	type(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if ((str[i] == '|' && str[i + 1] == '|')
		|| (str[i] == '&' && str[i + 1] == '&'))
		return ('G');
	else if (str[i] == '|')
		return ('P');
	else if (str[i] == '>' || str[i] == '<')
		return ('R');
	return (' ');
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	char			*temp;
	int				*len2;
	int				k;
	int				i;

	if (!s)
		return (NULL);
	i = -1;
	k = 0;
	temp = (char *)s;
	str = (char **)malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	len2 = &k;
	while (ft_word_count(s, c) > ++i)
	{
		temp = get_next_word(temp, c, len2);
		str[i] = (char *)malloc((*len2 + 2) * sizeof(char));
		str[i][0] = type(temp);
		if (!str[i])
			return (free_tab(str));
		ft_strlcpy(str[i], temp, (*(len2) + 1), 1);
	}
	return (str[i] = NULL, str);
}
