/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:40:23 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 14:40:24 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	dup_and_close(int for_dup, int for_close, char **args, int fd)
{
	if (dup2(for_dup, fd) == -1)
	{
		if (args && args[0])
			ft_errors_and_exit("dup2:", args[0], ": dup error.\n", FLAG_PERROR);
		ft_errors_and_exit("dup2:", 0, ": dup error.\n", FLAG_PERROR);
	}
	if (for_close != 0)
	{
		close(for_close);
	}
	return (0);
}

void	dup_in_child_proc(int i, t_exec_cmds *cmds, t_info_pipe *info)
{
	if (cmds->fd_from != -1)
		dup_and_close(cmds->fd_from, 0, cmds->args, STDIN_FILENO);
	else if (cmds->fd_from == -1 && i != 0)
		dup_and_close(info->fd[1 - info->pipe][0],
			info->fd[1 - info->pipe][0], cmds->args, STDIN_FILENO);
	if (cmds->fd_dest != -1)
		dup_and_close(cmds->fd_dest, 0, cmds->args, STDOUT_FILENO);
	else if (cmds->fd_dest == -1 && i != info->nbr - 1)
	{
		dup_and_close(info->fd[info->pipe][1],
			info->fd[info->pipe][0], cmds->args, STDOUT_FILENO);
		close(info->fd[info->pipe][1]);
	}
}
