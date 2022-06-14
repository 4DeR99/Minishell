/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:39:20 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:46:58 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cd_no_args(void)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (!home_path)
	{
		ft_putstr_fd("Minishell: cd: HOME not set", 2);
		g_glob.status = 1;
	}
	else
		chdir(home_path);
}

static void	replace_env_var(char *var, char *value)
{
	int		index;
	t_env	*env;

	env = g_glob.env;
	index = 0;
	while (env)
	{
		if (env->content[0] == var[0] && env->content[1] == var[1]
			&& env->content[2] == var[2] && env->content[3] == var[3])
			break ;
		env = env->next;
	}
	env->content = join_2(ft_strdup(var), value);
}

static void	execute_cd(char *path)
{
	if (!chdir(path))
		return ;
	else
	{
		perror(join_2(ft_strdup("bash: cd:"), path));
		g_glob.status = 1;
	}
}

void	cd_cmd(char **args)
{
	char	*path;
	char	*pwd;

	path = args[1];
	pwd = getcwd(NULL, 1024);
	if (!path)
		cd_no_args();
	else
		execute_cd(path);
	if (!getenv("OLDPWD"))
		envadd_back(g_glob.env, envnew(join_2("OLDPWD=", pwd), 1, 0));
	else
		replace_env_var("OLDPWD=", pwd);
	if (!getenv("PWD"))
		envadd_back(g_glob.env,
			envnew(join_2("PWD=", getcwd(NULL, 1024)), 1, 0));
	else
		replace_env_var("PWD=", getcwd(NULL, 1024));
}
