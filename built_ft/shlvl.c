/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:12:13 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 16:12:16 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_new_shlvl(char ***env)
{
	char	*tmp;
	int		indx;
	char	*char_lvl;
	char	*new_shlvl;

	tmp = find_line_env((*env), "SHLVL=", &indx);
	if ((!tmp))
	{
		if (export("SHLVL=1", env) == 1)
			return (1);
		return (0);
	}
	if (ft_strlen(tmp) == 7 && tmp[6] != '9')
		tmp[6] = tmp[6] + 1;
	else
	{
		char_lvl = ft_itoa((ft_atoi(&tmp[6]) + 1));
		new_shlvl = ft_strjoin("SHLVL=", char_lvl);
		free(char_lvl);
		if (!new_shlvl)
			return (ft_errors(0, "add shlvl", ": Error malloc.\n", 0));
		(*env)[indx] = new_shlvl;
		free (tmp);
	}
	return (0);
}
