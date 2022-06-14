/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:56:51 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/09 09:10:24 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmd_error(char *name)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (2);
}

static void	set_status(void)
{
	if (g_glob.status == 512)
		g_glob.status = 127;
	if (g_glob.status == 256)
		g_glob.status = 1;
}

int	exec_cmd(t_tree *tree, int ou, int in)
{
	int	pid;
	int	index;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGKILL, SIG_DFL);
		dup2(ou, 1);
		if (ou != 1)
			close(ou);
		dup2(in, 0);
		if (in != 0)
			close(in);
		index = check_for_wildcards(tree->cmd->args);
		while (index)
		{
			tree->cmd->args = up_flag(tree->cmd->args, tree->cmd->path);
			index = check_for_wildcards(tree->cmd->args);
		}
		if (execve(tree->cmd->path, tree->cmd->args, g_glob.env_tab) == -1)
			return (ft_cmd_error(tree->cmd->args[0]));
	}
	waitpid(pid, &g_glob.status, 0);
	set_status();
	return (g_glob.status);
}

void	run_pipe(t_tree *tree, int ou, int in)
{
	int	p[2];

	pipe(p);
	if (fork() == 0)
	{
		close(p[0]);
		if (ft_execution(tree->branch1, p[1], in) == 3)
			exit(1);
		close(p[1]);
		exit(0);
	}
	if (fork() == 0)
	{
		close(p[1]);
		if (ft_execution(tree->branch2, ou, p[0]) == 3)
			exit(1);
		close(p[0]);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
}

int	ft_execution(t_tree *tree, int ou, int in)
{
	if (tree->op != NULL)
	{
		if (ft_strcmp(tree->op, "&&") == 0 || ft_strcmp(tree->op, "||") == 0)
			run_and_or(tree, ou, in);
		else if (ft_strcmp(tree->op, "|") == 0)
			run_pipe(tree, ou, in);
		else if (ft_strcmp(tree->op, ">") == 0)
			run_redirect_output(tree, in);
		else if (ft_strcmp(tree->op, ">>") == 0)
			run_redirect_output_append(tree, in);
		else if (ft_strcmp(tree->op, "<") == 0)
			run_redirect_input(tree, ou);
		else if (ft_strcmp(tree->op, "<<") == 0)
			run_here_doc(tree, ou);
	}
	else
	{
		tree->cmd->args = split_cmd_nd_args(tree->cmd->name);
		tree->cmd->path = cmd_path(tree->cmd->args[0]);
		if (execute_builtins(tree->cmd->args, ou))
			return (g_glob.exc_status = 0, 0);
		else if (exec_cmd(tree, ou, in) == 0)
			return (g_glob.exc_status = 0, 0);
	}
	return (1);
}
