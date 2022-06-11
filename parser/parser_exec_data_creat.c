/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exec_data_creat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:58:20 by marugula          #+#    #+#             */
/*   Updated: 2022/06/09 11:28:55 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	proc_word(t_exec_cmds *data, t_words_lst *word)
{
	char		**wild_args;
	char		**temp;

	wild_args = wild_cards(word->content);
	if (wild_args == NULL)
		return (-1);
	temp = data->args;
	data->args = mass_strjoin(data->args, wild_args);
	free(temp);
	if (data->args == NULL)
		ft_errors_and_exit("malloc error:", "in proc_word", NULL, FLAG_PERROR);
	free(wild_args);
	return (0);
}

int	proc_pipe(t_exec_cmds **data)
{
	(*data)->next = ft_calloc(1, sizeof(t_exec_cmds));
	if ((*data)->next == NULL)
		return (-1);
	(*data) = (*data)->next;
	fill_default_val((*data));
	return (0);
}

t_exec_cmds	*creat_exec_data(t_words_lst *words)
{
	t_exec_cmds	*head;
	t_exec_cmds	*data;

	data = ft_calloc(1, sizeof(t_exec_cmds));
	if (data == NULL)
		return (NULL);
	fill_default_val(data);
	head = data;
	while (words != NULL)
	{
		if (words->content != NULL && words->is_who == ISWORD && \
										proc_word(data, words) == -1)
			return (clear_exec_cmds(head));
		if (words->is_who == HEREDOC && proc_heredoc(data, &words) == -1)
			return (clear_exec_cmds(head));
		if (is_redir_op(words->content) && proc_redir(data, &words) == -1)
			continue ;
		if (words->is_who == PIPE && proc_pipe(&data))
			return (clear_exec_cmds(head));
		words = words->next;
	}
	return (head);
}
