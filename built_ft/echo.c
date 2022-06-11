/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:47:29 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 18:02:38 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **lines, int fd)
{
	int	i;
	int	flag_nl;

	i = 0;
	flag_nl = 0;
	if (lines[i] && ft_memcmp(lines[i], "-n", 3) == 0)
	{
		flag_nl = 1;
		i++;
	}
	if (lines[i])
	{
		while (lines[i])
		{
			ft_putstr_fd(lines[i], fd);
			if (lines[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (flag_nl == 0)
		ft_putchar_fd('\n', fd);
	return (0);
}
