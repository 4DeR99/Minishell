/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_fnc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:37:14 by moulmado          #+#    #+#             */
/*   Updated: 2022/06/09 08:41:50 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_start_point(char **lst, int *size, t_tab *tab)
{
	int	opcount;

	opcount = 0;
	*size -= 2;
	while (*size > 0)
	{
		if (lst[*size][0] != ' ')
			opcount++;
		if (lst[*size][0] != ' ' && lst[*size - 1][0] == ' '
			&& lst[*size - 2][0] == ' ')
		{
			tab->start = *size - 2 - opcount + 1;
			break ;
		}
		*size -= 1;
	}
}
