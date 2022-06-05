#include "minishell.h"

void ft_lst_file(char *path ,t_stack **list, int *index)
{
	DIR                *dirp;
	struct dirent    *item;
	char *new_path;
	new_path = NULL;
	t_stack *node = (*list);
	dirp = opendir(path);
	item = readdir(dirp);
	while (item)
	{
		if(strcmp(item->d_name,".") != 0 && strcmp(item->d_name,"..") != 0)
		{
			ft_stackadd_back(&node,ft_stacknew(item->d_name,0));
			(*index)++;
		}
		item = readdir(dirp);
	}
	closedir(dirp);
}

char **make_lst_file(char *cmd)
{
	t_stack *node;
	int index = 1;
	char **str;

	node = ft_stacknew(cmd, 0);
	ft_lst_file(".", &node, &index);
	str = (char **)malloc(sizeof(char *) * index);
	index = 0;
	while (node)
	{
		str[index] = node->op;
		node = node->next;
		index++;
	}
	str[index] = NULL;
	return (str);
}

int	check_for_wildcards(char **flags)
{
	int	index;

	index = 0;
	while (flags[index])
	{
		if (ft_strcmp(flags[index], "*") == 0)
			return (index);
		index++;
	}
	return (0);
}

char	**up_flag(char **flags, char *cmd)
{
	int		flags_len;
	int		dir_len;
	char	**new_flags = NULL;
	char	**current_dir;

	(void)cmd;
	current_dir = make_lst_file(cmd);
	dir_len = 0;
	while (current_dir[dir_len])
		dir_len++;
	flags_len = 0;
	while (flags[flags_len])
		flags_len++;
	new_flags = (char **)malloc(sizeof(char *) * (flags_len + dir_len));
	flags_len = 0;
	int i = 0;
	while (flags[flags_len])
	{
		if (ft_strcmp(flags[flags_len], "*") == 0)
		{
			for (int j =0; j < dir_len;j++)
			{
				new_flags[i] = current_dir[j];
				i++;
			}
		}
		else
		{
			new_flags[i] = flags[flags_len];
			i++;
		}
		flags_len++;
	}
	new_flags[i] = NULL;
	return (new_flags);
}

int	exec_cmd(t_tree *tree, int ou, int in)
{
	int	pid = fork();
	int	index;

	set_env();
	if (pid == 0)
	{
		dup2(ou, 1);
		if (ou != 1)
			close(ou);
		dup2(in, 0);
		if (in != 0)
			close(in);
		if ((index = check_for_wildcards(tree->cmd->args)) != 0)
			tree->cmd->args = up_flag(tree->cmd->args, tree->cmd->path);
		if (execve(tree->cmd->path, tree->cmd->args, g_glob.env_tab) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(tree->cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_glob.status = 127;
			return (3);
		}
	}
	waitpid(pid, 0, 0);
	return (0);
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

int ft_execution(t_tree *tree, int ou, int in)
{
	if (!tree)
		exit(5);
	if (tree->op != NULL)
	{
		if (ft_strcmp(tree->op, "&&") == 0 || ft_strcmp(tree->op, "||") == 0)
			run_and_or(tree, ou, in);
		else if (ft_strcmp(tree->op, "|") == 0)
			run_pipe(tree, ou, in);
		else if (ft_strcmp(tree->op, ">") == 0)
			run_redirect_output(tree ,in);
		else if (ft_strcmp(tree->op, ">>") == 0)
			run_redirect_output_append(tree, in);
		else if (ft_strcmp(tree->op, "<") == 0)
			run_redirect_input(tree, ou, in);
		else if (ft_strcmp(tree->op, "<<") == 0)
			run_here_doc(tree, ou);
	}
	else
	{
		tree->cmd->args = split_cmd_nd_args(tree->cmd->name);
		if (exec_cmd(tree, ou, in) == 3)
			return (3);
	}
	return (1);
}