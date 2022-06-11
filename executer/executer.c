/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:03:25 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 12:30:54 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	cmd_is_path(char *cmdarg)
{
	if (cmdarg && cmdarg[0] && cmdarg[1] && cmdarg[0] == '.' \
									&& cmdarg[1] == '/')
	{
		return (1);
	}
	if (cmdarg && cmdarg[0] && cmdarg[0] == '/')
	{
		return (1);
	}
	return (0);
}

char	*check_paths( char *cmdarg, char **allpath)
{
	char	*pathcmd;

	if (cmdarg[0] == '\0' || cmdarg[0] == ' ')
	{
		errno = 2;
		ft_errors_and_exit(": ", cmdarg, NULL, FP);
	}
	if (cmd_is_path(cmdarg) == 1)
	{
		pathcmd = ft_strdup(cmdarg);
		if (pathcmd == 0)
			ft_errors_and_exit("path:", 0, ": malloc.\n", FP);
	}
	else
	{
		pathcmd = check_in_allpath(allpath, cmdarg);
		if (pathcmd)
			return (pathcmd);
	}
	pathcmd = ft_strdup(cmdarg);
	if (pathcmd == 0)
		ft_errors_and_exit("path:", 0, ": malloc.\n", FP);
	return (pathcmd);
}

int	ft_pipex_find_path(t_info_pipe *info)
{
	int	indx;

	info->path = find_line_env(g_data.env, "PATH=", &indx);
	info->allpath = NULL;
	if (info->path)
	{
		info->allpath = ft_split(info->path + 5, ':');
		if (info->allpath == 0)
			ft_errors_and_exit("split:", 0, ": malloc error.\n", FP);
	}
	return (0);
}

int	execut_in_child_proc(t_exec_cmds *cmds)
{
	int				pid;
	char			*pathcmd;
	t_info_pipe		info;
	int				status;

	pid = fork();
	if (pid == -1)
		ft_errors_and_exit("child:", 0, ": fork error.\n", 0);
	if (pid == 0)
	{
		back_to_dflt_signl();
		ft_pipex_find_path(&info);
		if (cmds->fd_from != -1)
			dup_and_close(cmds->fd_from, 0, cmds->args, STDIN_FILENO);
		if (cmds->fd_dest != -1)
			dup_and_close(cmds->fd_dest, 0, cmds->args, STDOUT_FILENO);
		pathcmd = check_paths(cmds->args[0], info.allpath);
		clearsplit(info.allpath);
		if (execve(pathcmd, cmds->args, g_data.env_hide) == -1)
			ft_errors_and_exit("execut:", cmds->args[0], " error.\n", FP);
	}
	waitpid(pid, &status, 0);
	g_data.our_errno = status_of_process(status);
	return (g_data.our_errno);
}

int	executer(t_exec_cmds *cmds)
{
	int	flag_cmd;

	if (cmds->next == NULL)
	{
		if (cmds->args)
		{
			flag_cmd = this_cmd_built_in(cmds->args[0]);
			if (flag_cmd == 0)
				execut_in_child_proc(cmds);
			else
				ex_in_parent_proc(cmds->args, flag_cmd, cmds, 0);
		}
		else
			g_data.our_errno = 1;
	}
	else
		pipex(cmds);
	return (0);
}
