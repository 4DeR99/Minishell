/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_of_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:13:08 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:42:27 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**lstlcpy(char **lst, int start, int end)
{
	char	**re;
	int		index;

	index = 0;
	re = (char **)malloc(sizeof(char *) * (end - start + 2));
	if (!re)
		return (NULL);
	while (start <= end)
		re[index++] = ft_strdup(lst[start++]);
	re[index] = NULL;
	return (re);
}

static t_tab	*split_cmd_lst(char **lst, int size, int s)
{
	t_tab	*tab;
	int		end;

	tab = malloc(sizeof(t_tab));
	if (!tab)
		return (NULL);
	tab->start = s;
	end = size - 2;
	if (tab->start)
		return (tab->lst = lstlcpy(lst, 0, tab->start - 1), tab);
	if (lst[size - 2][0] == ' ')
		tab->start = size - 2;
	else
		edit_start_point(lst, &size, tab);
	return (tab->lst = lstlcpy(lst, tab->start, end), tab);
}

static void	growing_branches(t_tree *tree, char **lst, int size)
{
	t_tree		*branch1;
	t_tree		*branch2;
	t_tab		*tab0;
	t_tab		*tab1;

	branch1 = malloc(sizeof(t_tree));
	branch2 = malloc(sizeof(t_tree));
	tree->branch1 = branch1;
	tree->branch2 = branch2;
	branch1->previous = tree;
	branch2->previous = tree;
	tab0 = split_cmd_lst(lst, size, 0);
	tree_expansion(branch2, tab0->lst);
	tab1 = split_cmd_lst(lst, size, tab0->start);
	tree_expansion(branch1, tab1->lst);
	free(tab0);
	free(tab1);
}

void	tree_expansion(t_tree *tree, char **lst)
{
	int		i;
	int		size;

	size = lst_size(lst);
	i = 0;
	if (lst[size - 1][0] != ' ')
	{
		tree->cmd = NULL;
		tree->op = ft_strdup(lst[size - 1] + 1);
		growing_branches(tree, lst, size);
	}
	else
	{
		tree->branch1 = NULL;
		tree->branch2 = NULL;
		tree->op = NULL;
		tree->cmd = malloc(sizeof(t_cmd));
		tree->cmd->name = ft_strdup(lst[0] + 1);
		tree->cmd->path = NULL;
		tree->cmd->args = NULL;
	}
	free_2d(lst);
}

t_tree	*tree_of_life(char **lst)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->previous = NULL;
	tree_expansion(tree, lst);
	return (tree);
}
