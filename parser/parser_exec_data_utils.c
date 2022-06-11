/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exec_data_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:03:18 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 17:30:05 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	proc_wildcard(char **content)
{
	char	**wildcard;

	wildcard = wild_cards(*content);
	if (mass_strlen(wildcard) != 1)
	{
		clear_arg_arr(wildcard);
		return (1);
	}
	free(*content);
	*content = wildcard[0];
	free(wildcard);
	return (0);
}

int	next_pipe_and_clear(char *text, t_words_lst **words, t_exec_cmds *data)
{
	ft_errors(NULL, (*words)->next->content, text, 0);
	data->args = clear_arg_arr(data->args);
	*words = find_next_pipe(*words);
	return (-1);
}

int	mass_strlen(char **lines)
{
	int	i;

	i = 0;
	while (lines && lines[i] != NULL)
		i++;
	return (i);
}

char	**mass_strjoin(char **first, char **second)
{
	char	**new;
	int		i;
	int		j;

	new = ft_calloc(mass_strlen(first) + mass_strlen(second) + 1, \
												sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (first && first[i] != NULL)
	{
		new[i] = first[i];
		i++;
	}
	j = 0;
	while (second && second[j] != NULL)
	{
		new[i + j] = second[j];
		j++;
	}
	return (new);
}
