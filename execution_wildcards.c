/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_wildcards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:50:01 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/07 06:49:36 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_file(char *path, t_stack **list, int *index)
{
	DIR				*dirp;
	struct dirent	*item;
	char			*new_path;
	t_stack			*node;

	new_path = NULL;
	node = (*list);
	dirp = opendir(path);
	item = readdir(dirp);
	while (item)
	{
		if (item->d_name[0] != '.')
		{
			ft_stackadd_back(&node, ft_stacknew(item->d_name, 0));
			(*index)++;
		}
		item = readdir(dirp);
	}
	closedir(dirp);
}

char	**make_lst_file(char *cmd)
{
	t_stack	*node;
	int		index;
	char	**str;
	t_stack	*head;

	index = 1;
	node = ft_stacknew(cmd, 0);
	ft_lst_file(".", &node, &index);
	str = (char **)malloc(sizeof(char *) * index);
	index = 0;
	head = node;
	while (node)
	{
		str[index] = node->op;
		node = node->next;
		index++;
	}
	free_list(&head);
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

static void	up_flags_utils(char **flags, char **c, char **new_flags, int *i)
{
	int	save;
	int	flags_len;
	int	dir_len;

	save = 0;
	flags_len = -1;
	dir_len = 0;
	while (flags[++flags_len])
	{
		if (ft_strcmp(flags[flags_len], "*") == 0 && save == 0)
		{
			save = 1;
			while (c[dir_len])
			{
				new_flags[*i] = c[dir_len];
				(*i)++;
				dir_len++;
			}
		}
		else
		{
			new_flags[*i] = flags[flags_len];
			(*i)++;
		}
	}
}

char	**up_flag(char **flags, char *cmd)
{
	int		flags_len;
	int		dir_len;
	char	**new_flags;
	char	**current_dir;
	int		i;

	(void)cmd;
	i = 0;
	new_flags = NULL;
	current_dir = make_lst_file(cmd);
	dir_len = 0;
	while (current_dir[dir_len])
		dir_len++;
	flags_len = 0;
	while (flags[flags_len])
		flags_len++;
	new_flags = (char **)malloc(sizeof(char *) * (flags_len + dir_len));
	up_flags_utils(flags + 1, current_dir, new_flags, &i);
	new_flags[i] = NULL;
	free_2d(flags);
	return (new_flags);
}
