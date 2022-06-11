/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:12:09 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 18:28:29 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int fd)
{
	char	*dir;
	int		len;

	len = PATH_MAX;
	dir = NULL;
	dir = getcwd(dir, len);
	if (dir == NULL)
		return (ft_errors("pwd: ", "getcwd", 0, FLAG_PERROR));
	write(fd, dir, ft_strlen(dir));
	write(fd, "\n", 1);
	free(dir);
	return (0);
}
