/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:51:58 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/03 20:03:14 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	rm_first_node(t_env *env)
{
	g_glob.env = g_glob.env->next;
	g_glob.env->previous = NULL;
	free(env->content);
	free(env);
}

static void	rm_last_node(t_env *env)
{
	t_env	*tmp;

	tmp = env->previous;
	tmp->next = NULL;
	free(env->content);
	free(env);
}

static void	middle_node_rm(t_env *env)
{
	t_env	*prev;
	t_env	*next;

	prev = env->previous;
	next = env->next;
	prev->next = next;
	next->previous = prev;
	free(env->content);
	free(env);
}

static void	rm_node(t_env *env)
{
	if (!env)
		return ;
	else if (!env->previous)
		rm_first_node(env);
	else if (!env->next)
		rm_last_node(env);
	else
		middle_node_rm(env);
}

void	unset_cmd(char **args)
{
	t_env	*env;
	int		i;

	i = 1;
	while (args[i])
	{
		env = g_glob.env;
		if (is_alpha_n(args[i][0]))
		{
			ft_putstr_fd("Minishell: export: `", 1);
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			g_glob.status = 1;
			return ;
		}
		while (env)
		{
			if (!ft_strcmp(ft_path_split(args[i], '=')[0],
				ft_path_split(env->content, '=')[0]))
				break ;
			env = env->next;
		}
		rm_node(env);
		i++;
	}
}
