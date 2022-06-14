/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:08:45 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/05 18:36:31 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	filr_error(char *name)
{
	printf("minishell : %s No such file or directory\n", name);
	exit(4);
}

char	*ft_command(char *str)
{
	int		len;
	char	*command;
	int		space;

	len = 0;
	space = 0;
	while (str[space] == ' ')
		space++;
	while (str[len + space] != ' ' && str[len + space])
		len++;
	command = malloc((len + 1));
	if (!command)
		return (NULL);
	len = 0;
	while (str[len + space] != ' ' && str[len + space])
	{
		command[len] = str[len + space];
		len++;
	}
	command[len] = '\0';
	return (command);
}

int	size_count(char **path)
{
	int	size;

	size = 0;
	while (path[size])
		size++;
	return (size);
}

char	*ft_optimize_path(char *path, char *command)
{
	int		size;
	char	*new_path;
	int		x;
	int		y;

	x = -1;
	y = 0;
	size = strlen(path) + strlen(command) + 2;
	new_path = malloc(size);
	if (!new_path)
		return (NULL);
	while (path[++x])
		new_path[x] = path[x];
	new_path[x] = '/';
	x++;
	while (command[y])
	{
		new_path[x] = command[y];
		x++;
		y++;
	}
	new_path[x] = '\0';
	return (new_path);
}
