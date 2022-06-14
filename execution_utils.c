/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:01:02 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/08 19:48:09 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_redirect_input(t_tree *tree, int ou)
{
	int		fd_in;
	t_tree	*tree_tmp;

	tree->branch2->cmd->args = split_cmd_nd_args(tree->branch2->cmd->name);
	fd_in = open(tree->branch2->cmd->args[0], O_RDONLY);
	while ((ft_strcmp(tree->branch1->op, "<") == 0
			|| ft_strcmp(tree->branch1->op, "<<") == 0)
		&& tree->branch1->op != NULL)
		tree = tree->branch1;
	tree_tmp = tree;
	while (tree_tmp != NULL && (ft_strcmp(tree_tmp->op, "<") == 0
			|| ft_strcmp(tree_tmp->op, "<<") == 0))
	{
		if (ft_strcmp(tree_tmp->op, "<") == 0
			&& access(tree_tmp->branch2->cmd->name, F_OK) == -1)
		{
			printf("Minishell: %s: No such file or directory\n",
				tree_tmp->branch2->cmd->args[0]);
			g_glob.status = 1;
			return ;
		}
			tree_tmp = tree_tmp->previous;
	}
	ft_execution(tree->branch1, ou, fd_in);
}

void	run_redirect_output(t_tree *tree, int in)
{
	int	fd_out;
	int	fd_tmp;

	tree->branch2->cmd->args = split_cmd_nd_args(tree->branch2->cmd->name);
	fd_out = open(tree->branch2->cmd->args[0],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	while ((ft_strcmp(tree->branch1->op, ">") == 0
			|| ft_strcmp(tree->branch1->op, ">>") == 0)
		&& tree->branch1->op != NULL)
	{
		tree = tree->branch1;
		fd_tmp = open(tree->branch2->cmd->name,
				O_RDWR | O_CREAT | O_TRUNC, 0777);
		close(fd_tmp);
	}
	if (fd_out != -1)
	{
		if (ft_execution(tree->branch1, fd_out, in) == 3)
			exit(0);
	}
	else
		printf("Minishell: %s: No such file or directory\n",
			tree->branch2->cmd->args[0]);
}

void	run_here_doc(t_tree *tree, int ou)
{
	t_tree	*tree_tmp;

	while ((ft_strcmp(tree->branch1->op, "<<") == 0
			|| ft_strcmp(tree->branch1->op, "<") == 0)
		&& tree->branch1->op != NULL)
		tree = tree->branch1;
	tree_tmp = tree->branch1;
	while ((ft_strcmp(tree_tmp->previous->op, "<<") == 0
			|| ft_strcmp(tree_tmp->previous->op, "<") == 0)
		&& tree_tmp->previous->previous != NULL
		&& (ft_strcmp(tree_tmp->previous->previous->op, "<<") == 0
			|| ft_strcmp(tree_tmp->previous->previous->op, "<") == 0))
	{
		if (ft_strcmp(tree_tmp->previous->op, "<") == 0)
		{
			if (access(tree_tmp->previous->branch2->cmd->name, F_OK) == -1)
				filr_error(tree_tmp->previous->branch2->cmd->name);
		}
			tree_tmp = tree_tmp->previous;
	}
	if (ft_execution(tree->branch1, ou, tree_tmp->previous->branch2->fd) == 3)
		return ;
}

void	run_redirect_output_append(t_tree *tree, int in)
{
	int	fd_out;
	int	fd_t;

	fd_out = open(tree->branch2->cmd->name, O_RDWR | O_CREAT | O_APPEND, 0644);
	while ((ft_strcmp(tree->branch1->op, ">") == 0
			|| ft_strcmp(tree->branch1->op, ">>") == 0)
		&& tree->branch1->op != NULL)
	{
		tree = tree->branch1;
		fd_t = open(tree->branch2->cmd->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		close(fd_t);
	}
	ft_execution(tree->branch1, fd_out, in);
}

void	run_and_or(t_tree *tree, int ou, int in)
{
	if (ft_strcmp(tree->op, "&&") == 0)
	{
		if (ft_execution(tree->branch1, ou, in) == 0)
			ft_execution(tree->branch2, ou, in);
	}
	else if (ft_execution(tree->branch1, ou, in) != 0)
		ft_execution(tree->branch2, ou, in);
}
