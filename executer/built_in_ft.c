/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:07:21 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 13:01:25 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	str_has_equal(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	this_cmd_built_in(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len == 0)
		return (0);
	if (ft_memcmp("cd", cmd, 2) == 0 && len == 2)
		return (CD);
	if (ft_memcmp("env", cmd, 3) == 0 && len == 3)
		return (ENV);
	if (ft_memcmp("pwd", cmd, 3) == 0 && len == 3)
		return (PWD);
	if (ft_memcmp("unset", cmd, 5) == 0 && len == 5)
		return (UNSET);
	if (ft_memcmp("export", cmd, 6) == 0 && len == 6)
		return (EXPORT);
	if (ft_memcmp("echo", cmd, 4) == 0 && len == 4)
		return (ECHO_CMD);
	if (ft_memcmp("exit", cmd, 4) == 0 && len == 4)
		return (EXIT);
	if (str_has_equal(cmd) == 1)
		return (EQUAL);
	return (0);
}

void	choose_built_in_cmd(char **cmd, int flag_cmd, int flag_pipex)
{
	if (flag_cmd == CD)
		g_data.our_errno = ft_cd(cmd[1]);
	else if (flag_cmd == ENV)
		g_data.our_errno = printf_env(g_data.env, 1);
	else if (flag_cmd == PWD)
		g_data.our_errno = ft_pwd(1);
	else if (flag_cmd == UNSET)
		g_data.our_errno = ft_unset(cmd[1], &g_data.env, &g_data.env_hide);
	else if (flag_cmd == EXPORT)
		g_data.our_errno = export(cmd[1], &g_data.env);
	else if (flag_cmd == ECHO_CMD)
		g_data.our_errno = ft_echo(&cmd[1], 1);
	else if (flag_cmd == EXIT)
		g_data.our_errno = ft_exit(&cmd[1], 1, flag_pipex);
	else if (flag_cmd == EQUAL)
		g_data.our_errno = export_in_hide(cmd[0]);
}

int	ex_in_parent_proc(char **cmd, int flag_cmd,
			t_exec_cmds *cmds, int flag_pipex)
{
	int	savefd;

	if (flag_pipex == 0 && cmds->fd_dest != -1)
	{
		savefd = dup(STDOUT_FILENO);
		if (dup2(cmds->fd_dest, STDOUT_FILENO) == -1 || savefd == -1)
			ft_errors_and_exit("dup:", cmd[0], ": dup error.\n", 0);
	}
	choose_built_in_cmd(cmd, flag_cmd, flag_pipex);
	if (flag_pipex == 0 && cmds->fd_dest != -1)
	{
		if (dup2(savefd, 1) == -1)
			ft_errors_and_exit("dup:", cmd[0], ": dup error.\n", 0);
	}
	return (g_data.our_errno);
}
