/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:27:46 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 12:31:38 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../minishell.h"

typedef struct s_info_pipe
{
	int		nbr;
	char	*path;
	char	**allpath;
	int		fd[2][2];
	int		pipe;
}	t_info_pipe;

int		this_cmd_built_in(char *cmd);
int		ft_echo(char **lines, int fd);
int		ft_cd(char *old_path);
int		ft_unset(char *str, char ***env, char ***second_env);
int		export_in_hide(char *new_line);
void	clearsplit(char **split);
char	*strjoin3(char *str1, char *str2, char *str3);
char	*check_paths( char *cmdarg, char **allpath);
int		pipex(t_exec_cmds *f_cmds);
int		ex_in_parent_proc(char **cmd, int flag_cmd,
			t_exec_cmds *cmds, int flag_pipex);
int		execut_in_child_proc(t_exec_cmds *cmds);
int		dup_and_close(int for_dup, int for_close, char **args, int fd);
void	dup_in_child_proc(int i, t_exec_cmds *cmds, t_info_pipe *info);
int		ft_pipex_find_path(t_info_pipe *info);
int		status_of_process(int status);
void	back_to_dflt_signl(void);
char	*check_in_allpath(char **allpath, char *cmdarg);

#endif