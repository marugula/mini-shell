/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:04:59 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 20:05:54 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	its_var_without_meaning(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=' && ((line[i + 1]
					&& line[i + 1] == '\0') || !line[i + 1]))
			return (1);
		else if (line[i] == '=' && line[i + 1] != '\0')
			return (0);
		i++;
	}
	return (0);
}

int	printf_env(char **env, int fd)
{
	int	count;
	int	count_symb;
	int	symb;

	count = 0;
	count_symb = 0;
	while (env[count])
	{
		symb = 0;
		while (env[count][symb])
		{
			symb++;
		}
		if (its_var_without_meaning(env[count]) == 0)
		{
			write (fd, env[count], symb);
			write (fd, "\n", 1);
			count_symb += symb;
		}
		count++;
	}
	return (count);
}
