/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word_list_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:12:30 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 15:29:55 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*end_of_word(char	*curent_p)
{
	while (*curent_p != 0 && !ft_isspace(*curent_p) && !is_token(curent_p) \
	&& !is_log_operator(curent_p))
	{
		if (*curent_p == SINGLEQM || *curent_p == DOUBLEQM)
			curent_p = find_next_quatation_mark(curent_p);
		if (curent_p == NULL)
		{
			ft_errors("QA marks", curent_p, NULL, 0);
			g_data.our_errno = ERROR_QMFIND;
			return (NULL);
		}
		curent_p++;
	}
	return (curent_p);
}

char	*next_word(char	*curent_p)
{
	while (*curent_p != 0 && ft_isspace(*curent_p))
		curent_p++;
	return (curent_p);
}

t_words_lst	*new_word_lst(void)
{
	t_words_lst	*lst;

	lst = ft_calloc(1, sizeof(t_words_lst));
	return (lst);
}

t_words_lst	*add_word_to_end_line(t_words_lst *head, char *word, int is_who)
{
	t_words_lst	*curent_lst;

	if (head == NULL)
	{
		head = new_word_lst();
		if (head == NULL)
			return (NULL);
		head->content = word;
		head->is_who = is_who;
		return (head);
	}
	curent_lst = head;
	while (curent_lst->next != NULL)
		curent_lst = curent_lst->next;
	curent_lst->next = new_word_lst();
	if (curent_lst->next == NULL)
		return (NULL);
	curent_lst->next->prev = curent_lst;
	curent_lst->next->content = word;
	curent_lst->next->is_who = is_who;
	return (head);
}

t_words_lst	*find_next_pipe(t_words_lst *curent_word)
{
	while (curent_word != NULL && curent_word->is_who != PIPE)
	{
		curent_word = curent_word->next;
	}
	return (curent_word);
}
