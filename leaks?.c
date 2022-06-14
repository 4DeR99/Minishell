/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks?.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:23:37 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/07 16:06:29 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}

static void	free_cmd_node(t_tree *tree)
{
	free(tree->cmd->name);
	if (tree->cmd->args)
		free_2d(tree->cmd->args);
	if (tree->cmd->path)
		free(tree->cmd->path);
	free(tree->cmd);
	free(tree);
}

static void	free_op_node(t_tree *tree)
{
	free(tree->op);
	free(tree);
}

void	tree_free(t_tree *tree, t_tree *branch1, t_tree	*branch2)
{
	if (tree->cmd)
	{
		free_cmd_node(tree);
		return ;
	}
	if (branch1->cmd)
		free_cmd_node(branch1);
	else
		tree_free(branch1, branch1->branch1, branch1->branch2);
	if (branch2->cmd)
		free_cmd_node(branch2);
	else
		tree_free(branch2, branch2->branch1, branch2->branch2);
	free_op_node(tree);
}
