/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word_list_creat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:55:55 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 15:29:18 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*skip_isspace(char *curent_p)
{
	while (*curent_p && ft_isspace(*curent_p))
		curent_p++;
	return (curent_p);
}

static int	proc_log_op(t_words_lst **head)
{
	*head = add_word_to_end_line(*head, ft_strdup("|"), PIPE);
	if (head == NULL)
		ft_errors_and_exit("Malloc in 'proc_log_op'", \
		":", NULL, FLAG_PERROR);
	return (1);
}

static int	proc_redir_op(t_words_lst **head, char *curent_p)
{
	char	*word;

	if (is_redir_op(curent_p) == REDIRIN || is_redir_op(curent_p) == REDIROUT)
		word = ft_strdupl(curent_p, 1);
	else
		word = ft_strdupl(curent_p, 2);
	if (word == NULL)
		ft_errors_and_exit("Malloc in 'proc_red_op'", \
			":", NULL, FLAG_PERROR);
	*head = add_word_to_end_line(*head, word, is_redir_op(curent_p));
	if (head == NULL)
		ft_errors_and_exit("Malloc in 'proc_red_op'", \
			":", NULL, FLAG_PERROR);
	return (ft_strlen(word));
}

static char	*proc_args(t_words_lst **head, char *curent_p)
{
	char	*end_word;
	char	*word;

	end_word = end_of_word(curent_p);
	if (end_word == NULL)
		return (clear_word_lst(*head));
	word = ft_strdupl(curent_p, end_word - curent_p);
	if (word == NULL)
		ft_errors_and_exit("Malloc in 'proc_word_'", \
			":", NULL, FLAG_PERROR);
	*head = add_word_to_end_line(*head, word, ISWORD);
	if (*head == NULL)
		ft_errors_and_exit("Malloc in 'proc_word_'", \
				":", NULL, FLAG_PERROR);
	return (end_word);
}

t_words_lst	*creat_word_list(char *line)
{
	char		*curent_p;
	t_words_lst	*head_words_line;

	head_words_line = NULL;
	curent_p = line;
	while (*curent_p)
	{
		curent_p = skip_isspace(curent_p);
		if (is_log_operator(curent_p))
			curent_p += proc_log_op(&head_words_line);
		else if (is_redir_op(curent_p))
			curent_p += proc_redir_op(&head_words_line, curent_p);
		else if (*curent_p)
		{
			curent_p = proc_args(&head_words_line, curent_p);
			if (curent_p == NULL)
				return (NULL);
		}
	}
	return (head_words_line);
}
