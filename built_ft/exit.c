/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:18:30 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 18:33:55 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_line_for_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 && ((i != 0 && line[i] != '-') || \
		(i != 0 && line[i] != '+')))
		{
			return (255);
		}
		i++;
	}
	return (0);
}

long	find_res_exit(char *line)
{
	long	res;
	char	res_c;

	res = ft_atol(line);
	res_c = (char) res;
	if ((res == 9223372036854775807
			&& ft_strncmp(line, "9223372036854775807", 19) != 0)
		|| (res == -9223372036854775807L - 1L
			&& ft_strncmp(line, "-9223372036854775808", 20) != 0))
	{
		ft_errors("exit: ", line, ": numeric argument required\n", 0);
		res_c = (char) 255;
	}
	return (res_c);
}

int	ft_exit(char **line, int flag, int flag_pipe)
{
	long	res;

	if (flag_pipe == 0)
		write(2, "exit\n", 5);
	if (flag == 0)
		exit(0);
	res = g_data.our_errno;
	if (line[0])
	{
		res = check_line_for_exit(line[0]);
		if (res == 255)
			ft_errors("exit: ", line[0], ": numeric argument required\n", 0);
		else if (res == 0)
		{
			if (!line[1])
			{
				res = find_res_exit(line[0]);
			}
			else
				return (ft_errors(0, "exit: ", "too many arguments\n", 0));
		}
	}
	exit(res);
	return (res);
}
