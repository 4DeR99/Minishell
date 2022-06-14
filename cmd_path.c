/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:46:51 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/08 20:30:45 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	**new_path(char **path, char *command)
{
	int		x;
	int		array_size;
	char	**new_path;

	array_size = size_count(path);
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
	set_env();
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
	char	*tmp;

	if (access(new_command, F_OK) == 0 && access(new_command, X_OK) == 0)
		return (ft_strdup(new_command));
	x = 0;
	while (new_path[x])
	{
		tmp = new_path[x];
		if (access(tmp, F_OK) == 0
			&& access(tmp, X_OK) == 0)
			return (ft_strdup(new_path[x]));
		x++;
	}
	return (NULL);
}

char	*cmd_path(char *cmd)
{
	char	*str;
	char	**path;
	char	*ret;
	char	**tmp;

	g_glob.exc_status = 1;
	set_env();
	str = getenv("PATH");
	path = ft_path_split(str, ':');
	tmp = path;
	path = new_path(path, cmd);
	ret = ft_path(cmd, path);
	free_array(path);
	free_array(tmp);
	return (ret);
}
