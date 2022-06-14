/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:07:23 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/14 18:10:18 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_it(char *str, t_env *env)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i] == '=' && !quotes)
		{
			ft_putchar_fd('"', 1);
			quotes = 1;
		}
		i++;
	}
	if (quotes)
		ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
	env->isprinted = 1;
}

static void	no_args(void)
{
	char	*small;
	t_env	*env;
	t_env	*node;
	int		i;

	i = 0;
	while (i < envsize(g_glob.env))
	{
		env = g_glob.env;
		while (env->isprinted)
			env = env->next;
		small = env->content;
		node = env;
		while (env)
		{
			if (!env->isprinted && ft_strcmp(small, env->content) > 0)
			{
				small = env->content;
				node = env;
			}
			env = env->next;
		}
		put_it(small, node);
		i++;
	}
}

static int	equal_check(char *str)
{
	int	index;

	index = 1;
	while (str[index])
		if (str[index++] == '=')
			return (1);
	return (0);
}

static void	add_var(char *str)
{
	t_env	*env;

	env = g_glob.env;
	if (is_alpha_n(str[0]))
	{
		ft_putstr_fd("Minishell: export: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier", 1);
		ft_putchar_fd('\n', 1);
		g_glob.status = 1;
		return ;
	}
	while (env)
	{
		if (!ft_strcmp(str, env->content))
			break ;
		env = env->next;
	}
	if (env && equal_check(str))
	{
		free(env->content);
		env->content = ft_strdup(str);
	}
	else
		envadd_back(g_glob.env, envnew(ft_strdup(str), equal_check(str), 0));
}

void	export_cmd(char **args)
{
	int	index;

	index = 1;
	if (!args[1])
		no_args();
	else
		while (args[index])
			add_var(args[index++]);
	reset();
}
