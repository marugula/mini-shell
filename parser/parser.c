/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:06:33 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 19:18:52 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_words_lst	*replace_dollar(t_words_lst *words)
{
	t_words_lst	*head;

	head = words;
	while (words != NULL)
	{
		if (words->is_who == HEREDOC)
			words = words->next;
		else if (words->is_who == ISWORD)
			words->content = check_dllr_line(words->content, IN_NOTHEREDOC);
		words = words->next;
	}
	return (head);
}

void	set_prev(t_exec_cmds *head)
{
	t_exec_cmds	*curent;
	t_exec_cmds	*prev;

	prev = NULL;
	curent = head;
	while (curent)
	{
		curent->prev = prev;
		prev = curent;
		curent = curent->next;
	}
}

t_exec_cmds	*parser(char	*line)
{
	t_words_lst	*head_words_line;
	t_exec_cmds	*exec_cmds;
	char		*status_check;

	head_words_line = creat_word_list(line);
	if (head_words_line == NULL)
		return (NULL);
	status_check = check_syntax(head_words_line);
	if (status_check != NULL)
	{
		g_data.our_errno = ERROR_UNEXPOP;
		ft_errors("Unexpected el : \"", status_check, "\"\n", 0);
		return (clear_word_lst(head_words_line));
	}
	head_words_line = replace_dollar(head_words_line);
	exec_cmds = creat_exec_data(head_words_line);
	set_prev(exec_cmds);
	clear_word_lst(head_words_line);
	return (exec_cmds);
}
