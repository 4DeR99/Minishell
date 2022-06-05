#include"minishell.h"

char	*ft_read(void)
{
	int		i;
	int		x;
	char	buffer[800000];
	char	l[2];

	x = 1;
	i = 0;
	while (x)
	{
		x = read(0, l, 1);
		if (x == -1)
			return (NULL);
		buffer[i] = l[0];
		if (l[0] == '\n' || x == 0)
			break ;
		i++;
	}
	if (x == 0)
		return (NULL);
	buffer[i] = '\n';
	i++;
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

char	*var_name(char *line)
{
	int		len;
	char	*var;
	int		x;

	x = 0;
	len = 0;
	while (line[x] != '$' && line[x])
		x++;
	len = x + 1;
	while (is_alpha_n(line[len]) == 0 && line[len] != '\0' && line[len] != '\n')
		len++;
	var = malloc(len - x);
	if (!var)
		return (NULL);
	len = x + 1;
	x = 0;
	while (is_alpha_n(line[len]) == 0 && line[len] != '\0' && line[len] != '\n')
	{
		var[x] = line[len];
		x++;
		len++;
	}
	var[len] = '\0';
	return (var);
}

int	ft_get_line(char *line)
{
	int	len;
	int	len_;

	if (!line)
		return (0);
	len = 0;
	len_ = 1;
	while (line[len] != '$' && line[len] != '\0')
		len++;
	len_ = len + 1;
	while (is_alpha_n(line[len_]) == 0 && line[len_] != '\0')
		len_++;
	while (line[len + len_] != '\0')
		len++;
	return (len);
}