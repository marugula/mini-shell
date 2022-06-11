/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:53:16 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 16:55:32 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*check_syntax(t_words_lst *head)
/* returns an unexpected element or NULL when everything is ok */
{
	t_words_lst	*curent_lst;

	curent_lst = head;
	while (curent_lst != NULL)
	{
		if (is_log_operator(curent_lst->content))
		{
			if (curent_lst->next == NULL || curent_lst->prev == NULL)
				return (curent_lst->content);
			if (curent_lst->next->is_who == PIPE)
				return (curent_lst->content);
		}
		else if (is_redir_op(curent_lst->content))
		{
			if (curent_lst->next == NULL)
				return (curent_lst->content);
			if (curent_lst->next->is_who != ISWORD)
				return (curent_lst->next->content);
		}
		curent_lst = curent_lst->next;
	}
	return (NULL);
}
