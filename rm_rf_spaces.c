/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_rf_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:28:25 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/01 20:57:00 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pos(char *str)
{
	int	index;
	int	re;

	index = slen(str) - 1;
	while (index >= 0 && str[index] == ' ')
	{
		re = index;
		index--;
	}
	re = index;
	return (re);
}

static char	*cleanse(char *str)
{
	int		index;
	int		start;
	char	*re;
	int		end;

	end = pos(str);
	start = 0;
	while (str[start] == ' ' && str[start])
		start++;
	re = (char *)malloc(sizeof(char) * (end - start + 2));
	index = 0;
	while (start <= end)
		re[index++] = str[start++];
	re[index] = '\0';
	// free(str);
	return (re);
}

void	rm_rf_spaces(t_tree *tree)
{
	t_tree	*tree_tmp;

	tree_tmp = tree;
	while (tree->branch1)
		tree = tree->branch1;
	while (tree)
	{
		if (tree->cmd)
			tree->cmd->name = cleanse(tree->cmd->name);
		else if (tree->branch2)
			rm_rf_spaces(tree->branch2);
		if (tree == tree_tmp)
			break ;
		tree = tree->previous;
	}
}