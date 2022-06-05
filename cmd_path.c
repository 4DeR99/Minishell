/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:46:51 by moulmado          #+#    #+#             */
/*   Updated: 2022/05/27 14:54:03 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	*ft_command(char *str)
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

static int	ft_size_count(char **path)
{
	int	size;

	size = 0;
	while (path[size])
		size++;
	return (size);
}

static char	*ft_optimize_path(char *path, char *command)
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

static char	**new_path(char **path, char *command)
{
	int		x;
	int		array_size;
	char	**new_path;

	array_size = ft_size_count(path);
	new_path = (char **)malloc((array_size + 1) * sizeof(char *));
	if (!new_path)
		return (NULL);
	x = 0;
	while (path[x])
	{
		new_path[x] = ft_optimize_path(path[x], command);
		x++;
	}
	new_path[x] = NULL;
	return (new_path);
}

static int	check_name(char *str, size_t *l, const char *path)
{
	size_t		x;

	x = 0;
	while (str[x])
	{
		if (str[x] != path[x])
			break ;
		x++;
	}
	if (x == ft_strlen(path))
	{
		*l = x;
		return (1);
	}
	else
		return (0);
}

char	*ft_find_path(const char *path)
{
	size_t	x;
	size_t	*l;
	size_t	y;

	y = 0;
	x = 0;
	l = &y;
	while (g_glob.env_tab[x])
	{
		if (check_name(g_glob.env_tab[x], l, path) == 1
			&& g_glob.env_tab[x][*l] == '=')
			return (g_glob.env_tab[x] + (*l + 1));
		x++;
	}
	return (NULL);
}

static char	*ft_path(char *new_command, char **new_path)
{
	int		x;

	if (access(new_command, F_OK) == 0 && access(new_command, X_OK) == 0)
		return (new_command);
	x = 0;
	while (new_path[x])
	{
		if (access(ft_command(new_path[x]), F_OK) == 0
			&& access(ft_command(new_path[x]), X_OK) == 0)
			return (new_path[x]);
		x++;
	}
	return (NULL);
}

char *cmd_path(char *cmd)
{
	char	*str = getenv("PATH");
    char	**path = ft_path_split(str, ':');
	path = new_path(path,ft_command(cmd));
    return(ft_path(ft_command(cmd),path));
}