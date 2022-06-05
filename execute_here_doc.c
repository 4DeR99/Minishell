/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 04:01:21 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/04 14:34:20 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_del(t_tree *tree)
{
	int	p[2];

	pipe(p);
	read_from_here_doc(p[1], tree->cmd->name);
	tree->cmd = NULL;
	tree->fd = p[0];
	close(p[1]);
}

void	here_doc_execute(t_tree *tree)
{
	t_tree	*tree_tmp;

	tree_tmp = tree;
	while (tree->branch1)
		tree = tree->branch1;
	while (tree)
	{
		if (ft_strcmp(tree->op, "<<") == 0 && tree->op)
		{
			replace_del(tree->branch2);
		}
		else if (tree->branch2)
		{
			if (tree->branch2->op)
				here_doc_execute(tree->branch2);
		}
		if (tree == tree_tmp)
			break ;
		tree = tree->previous;
	}
}
