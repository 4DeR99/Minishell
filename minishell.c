/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:58:44 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/04 13:43:11 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

int	ft_size_count(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

void	envdup(char **env)
{
	t_env	*new_env;
	int		index;

	rl_catch_signals = 0;
	new_env = envnew(env[0], 1, 0);
	index = 1;
	while (env[index])
		envadd_back(new_env, envnew(ft_strdup(env[index++]), 1, 0));
	g_glob.env = new_env;
	g_glob.home = getenv("HOME");
}

void	set_env(void)
{
	int		index;
	int		size;
	t_env	*env_tmp;

	env_tmp = g_glob.env;
	size = envsize(g_glob.env);
	index = 0;
	if (g_glob.env_tab)
		free(g_glob.env_tab);
	g_glob.env_tab = malloc(sizeof(char *) * size + 1);
	while (index < size)
	{
		g_glob.env_tab[index] = env_tmp->content;
		index++;
		env_tmp = env_tmp->next;
	}
	g_glob.env_tab[index] = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_tree	*tree;

	(void)ac;
	(void)av;
	signal(2, sighandler);
	signal(SIGQUIT, sighandler);
	envdup(env);
	while (1)
	{
		g_glob.status = 0;
		input = readline(PROMPT);
		if (input != NULL && input[0] != '\0')
			add_history(input);
		tree = parser(input);
		if (tree)
			ft_execution(tree, 1, 0);
		free(input);
	}
}
