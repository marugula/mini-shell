/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:13:52 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 11:19:52 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	execute_cmd(t_exec_cmds *cmds, t_info_pipe *info)
{
	int		flag_cmd;

	if (cmds->args)
	{
		flag_cmd = this_cmd_built_in(cmds->args[0]);
		if (flag_cmd == 0)
		{
			g_data.our_errno = execut_in_child_proc(cmds);
		}
		else
		{
			g_data.our_errno = ex_in_parent_proc(cmds->args, flag_cmd, cmds, 1);
		}
	}
	else
		g_data.our_errno = 1;
	close(info->fd[1 - info->pipe][0]);
	close(info->fd[info->pipe][1]);
	exit (g_data.our_errno);
	return (0);
}

int	count_cmds(t_exec_cmds *cmds)
{
	int			count;
	t_exec_cmds	*f_cmds;

	count = 0;
	f_cmds = cmds;
	while (f_cmds)
	{
		count++;
		f_cmds = f_cmds->next;
	}
	return (count);
}

int	executer_pipex_cmd(int i, t_exec_cmds *cmds, t_info_pipe *info, pid_t *pid)
{
	if (pipe(info->fd[info->pipe]) < 0)
		ft_errors_and_exit("child:", 0, ": pipe error.\n", FLAG_PERROR);
	pid[i] = fork();
	if (pid[i] < 0)
		ft_errors_and_exit("child:", 0, ": fork error.\n", FLAG_PERROR);
	if (pid[i] == 0)
	{
		back_to_dflt_signl();
		dup_in_child_proc(i, cmds, info);
		execute_cmd(cmds, info);
	}
	close(info->fd[1 - info->pipe][0]);
	close(info->fd[info->pipe][1]);
	return (0);
}

void	creat_pid_pipex(t_info_pipe	*info, pid_t **pid, t_exec_cmds *f_cmds)
{
	t_exec_cmds	*cmds;

	cmds = f_cmds;
	info->nbr = count_cmds(cmds);
	info->pipe = 0;
	*pid = (pid_t *) malloc (sizeof(pid_t) * info->nbr);
	if (!*pid)
		ft_errors_and_exit("pid:", 0, ": error.\n", FLAG_PERROR);
}

int	pipex(t_exec_cmds *f_cmds)
{
	t_info_pipe	info;
	int			status;
	t_exec_cmds	*cmds;
	int			i;
	pid_t		*pid;

	i = 0;
	pid = NULL;
	creat_pid_pipex(&info, &pid, f_cmds);
	cmds = f_cmds;
	while (cmds)
	{
		executer_pipex_cmd(i, cmds, &info, pid);
		i++;
		cmds = cmds->next;
		info.pipe = 1 - info.pipe;
	}
	i = 0;
	while (i < info.nbr)
		waitpid(pid[i++], &status, 0);
	free(pid);
	g_data.our_errno = status_of_process(status);
	return (g_data.our_errno);
}
