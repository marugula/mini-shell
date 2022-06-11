/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_proc_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:31:50 by marugula          #+#    #+#             */
/*   Updated: 2022/06/09 11:55:25 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../wild_c/wild_card.h"

int	proc_redirin(t_exec_cmds *data, t_words_lst **words)
{
	if (data->fd_from != -1)
	{
		close(data->fd_from);
		data->fd_from = -1;
	}
	if (access(".heredoc", F_OK) == 0)
		unlink_heredoc_fd();
	if (proc_wildcard(&((*words)->next->content)) == 1)
		return (next_pipe_and_clear(": ambiguous redirect\n", words, data));
	data->fd_from = open_file((*words)->next->content, O_RDONLY);
	if (data->fd_from == -1)
	{
		data->args = clear_arg_arr(data->args);
		*words = find_next_pipe(*words);
		return (-1);
	}
	return (0);
}

int	proc_redirout(t_exec_cmds *data, t_words_lst **words, int mod)
{
	if (data->fd_dest > 2)
	{
		close(data->fd_dest);
		data->fd_dest = -1;
	}
	if (proc_wildcard(&((*words)->next->content)) == 1)
		return (next_pipe_and_clear(": ambiguous redirect\n", words, data));
	data->fd_dest = open_file((*words)->next->content, mod);
	if (data->fd_dest == -1)
	{
		data->args = clear_arg_arr(data->args);
		*words = find_next_pipe(*words);
		return (-1);
	}
	return (0);
}

int	proc_redir(t_exec_cmds *data, t_words_lst **words)
{
	if ((*words)->is_who == REDIRIN)
		if (proc_redirin(data, words) == -1)
			return (-1);
	if ((*words)->is_who == REDIROUT)
		if (proc_redirout(data, words, O_CREAT | O_WRONLY | O_TRUNC) == -1)
			return (-1);
	if ((*words)->is_who == REDIROUTAP)
		if (proc_redirout(data, words, O_WRONLY | O_CREAT | O_APPEND) == -1)
			return (-1);
	(*words) = (*words)->next;
	return (0);
}

int	make_heredoc(char *stop)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_errors_and_exit("child:", 0, ": fork error.\n", 0);
	if (pid == 0)
		start_heredoc(stop);
	waitpid(pid, &status, 0);
	g_data.our_errno = status_of_process(status);
	if (g_data.our_errno != 0)
		exit(1);
	return (open_heredoc_fd());
}

int	proc_heredoc(t_exec_cmds *data, t_words_lst **words)
{
	char	**stop;

	if (data->fd_from > 2)
	{
		close(data->fd_from);
		data->fd_from = -1;
	}
	if (access(".heredoc", F_OK) == 0)
		unlink_heredoc_fd();
	stop = delete_quotes_from_line((*words)->next->content);
	data->fd_from = make_heredoc(stop[0]);
	clear_arg_arr(stop);
	*words = (*words)->next;
	return (0);
}
