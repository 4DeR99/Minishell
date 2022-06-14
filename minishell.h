/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:58:57 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/14 18:09:57 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED 0
# define BLUE 1
# define CYAN 2
# define YELLOW 3
# define WHITE 4
# define GREEN 5
# define EXODIA 666
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>

# define PROMPT "➜  mminishell ✗ "

typedef struct s_env
{
	char			*content;
	int				isenv;
	int				isprinted;
	struct s_env	*previous;
	struct s_env	*next;
}				t_env;

typedef struct s_glob
{
	int		status;
	char	*home;
	char	**env_tab;
	t_env	*env;
	int		exc_status;
}				t_glob;

typedef struct s_stack
{
	int				prio;
	char			*op;
	struct s_stack	*prev;
	struct s_stack	*next;
}				t_stack;

typedef struct s_int
{
	int	len;
	int	tmp;
	int	yes;
	int	prio;
}				t_int;
typedef struct s_tab
{
	char	**lst;
	int		start;
}				t_tab;

typedef struct s_cmd
{
	char	**args;
	char	*name;
	char	*path;
}				t_cmd;

//tree
typedef struct s_tree
{
	struct s_tree	*previous;
	struct s_tree	*branch1;
	struct s_tree	*branch2;
	t_cmd			*cmd;
	char			*op;
	int				fd;
	int				branch_type;
}				t_tree;

t_glob			g_glob;
extern t_glob	g_glob;

//utils
char	*ft_strjoin(char *s0, char *s1);
char	*join_ndfree(char *s0, char *s1);
char	*join_2(char *s0, char *s1);
int		slen(char *c);
int		ft_strchr(char *str, int c);
char	*ft_strdup(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
int		lst_size(char **lst);
size_t	ft_strlen(const char *str);
char	**ft_path_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		is_alpha_n(char c);
void	set_env(void);
int		ft_atoi(const char *s);
char	*ft_itoa(int nbr);
void	reset(void);

//4 parce
t_tree	*parser(char *input);
int		check_syntax(char *input);
int		check_4_parentheses(char *input);
int		check_4_quotes(char *input);
char	*postfix_expression(char *line);
char	*postfix_handl(char *line, char *poxfix,
			t_stack **stack, t_int *ints);
char	*get_op_nd_cmd(char *line, t_stack **stack, t_int *ints, int yes);
void	tree_expansion(t_tree *tree, char **lst);
t_tree	*tree_of_life(char **lst);
void	edit_start_point(char **lst, int *size, t_tab *tab);
void	rm_rf_spaces(t_tree *tree);
char	**split_cmd_nd_args(char *args);
char	**multiple_args(char *args);
char	*expand_var(char *str);
char	*rm_quotes(char *str);
char	*variable_name(char *line);

//fix_post
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t destsize, int start);

//stacklst
int		ft_stacksize(t_stack *lst);
void	ft_stackadd_back(t_stack **lst, t_stack *new);
t_stack	*ft_stacklast(t_stack *lst);
void	ft_stackdellast(t_stack **stack);
t_stack	*ft_stacknew(char *op, int prio);
void	ft_stackdelone(t_stack *lst, void (*del)(void *));

//envlst
t_env	*envnew(char *content, int isenv, int isprinted);
void	envadd_back(t_env *env, t_env *new);
t_env	*envlast(t_env *env);
int		envsize(t_env *env);

//execution
void	here_doc_execute(t_tree *tree);
int		ft_execution(t_tree *tree, int ou, int in);
char	*cmd_path(char *cmd);
char	*ft_find_path(const char *path);
void	run_redirect_input(t_tree *tree, int ou);
void	run_redirect_output(t_tree *tree, int in);
void	run_here_doc(t_tree *tree, int ou);
void	run_redirect_output_append(t_tree *tree, int in);
void	run_and_or(t_tree *tree, int ou, int in);
char	*ft_optimize_path(char *path, char *command);
char	*ft_command(char *str);
int		size_count(char **path);
void	filr_error(char *name);
int		execute_builtins(char **args, int ou);

//here_doc_functions
int		read_from_here_doc(int fd_in, char *limiter);
char	*ft_read(void);
char	*var_name(char *line);
int		ft_get_line(char *line);

//built_ins
void	pwd_cmd(int ou);
void	cd_cmd(char **args);
void	env_cmd(void);
void	echo_cmd(char **args, int ou);
void	export_cmd(char **args);
void	unset_cmd(char **args);
void	exit_cmd(char **args);

//wildcards
void	ft_lst_file(char *path, t_stack **list, int *index);
char	**make_lst_file(char *cmd);
int		check_for_wildcards(char **flags);
char	**up_flag(char **flags, char *cmd);

//leaks?
void	free_2d(char **lst);
void	free_list(t_stack **stack);
void	tree_free(t_tree *tree, t_tree *branch1, t_tree	*branch2);
void	free_array(char **array);
void	sighandler(int sig);

#endif