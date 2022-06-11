/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:07:46 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 11:28:44 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "wild_card.h"

int	delete_quotes_from_parts(t_part *parts)
{
	t_part		*f_parts;
	t_quotes	inf;

	f_parts = parts;
	set_dflt_t_quotes(&inf);
	while (f_parts)
	{
		inf.i = 0;
		inf.j = 0;
		while (f_parts->line && f_parts->line[inf.i])
		{
			if (f_parts->line[inf.i] == '\'' && inf.quotes2 % 2 == 0)
				inf.quotes++;
			else if (f_parts->line[inf.i] == '"' && inf.quotes % 2 == 0)
				inf.quotes2++;
			else
				f_parts->line[inf.j++] = f_parts->line[inf.i];
			inf.i++;
			if (f_parts->line[inf.i] == '\0')
				f_parts->line[inf.j] = '\0';
		}
		f_parts = f_parts->next;
	}
	return (0);
}

char	**delete_quotes_from_line(char *line)
{
	t_quotes	inf;
	char		**rez;

	set_dflt_t_quotes(&inf);
	while (line && (line)[inf.i])
	{
		if ((line)[inf.i] == '\'' && inf.quotes2 % 2 == 0)
			inf.quotes++;
		else if ((line)[inf.i] == '"' && inf.quotes % 2 == 0)
			inf.quotes2++;
		else
			line[inf.j++] = (line)[inf.i];
		inf.i++;
		if ((line)[inf.i] == '\0')
			line[inf.j] = '\0';
	}
	if (line[0] == '\0')
	{
		rez = ft_calloc(2, sizeof(char *));
		rez[0] = ft_calloc(1, sizeof(char));
		rez[1] = NULL;
	}
	else
		rez = ft_split(line, '\0');
	return (rez);
}

char	**ft_save_meaning(t_part *meaning)
{
	t_part	*mean;
	char	**res;
	int		i;

	mean = meaning;
	i = 0;
	while (mean)
	{
		i++;
		mean = mean->next;
	}
	res = ft_calloc(sizeof(char *), i);
	if (!res)
		ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FLAG_PERROR);
	i = 0;
	mean = meaning;
	while (mean->line)
	{
		res[i] = ft_strdup(mean->line);
		i++;
		mean = mean->next;
	}
	res[i] = NULL;
	return (res);
}

char	**wild_cards(char *line)
{
	t_part	*parts;
	char	**res;
	t_part	*meaning;

	if (is_star_in_line(line) == -1)
		return (delete_quotes_from_line(line));
	parts = find_parts(line);
	if (!parts)
		return (delete_quotes_from_line(line));
	delete_quotes_from_parts(parts);
	meaning = find_meaning_star(parts);
	free_parts(parts);
	if (meaning)
	{
		res = ft_save_meaning(meaning);
		free_parts(meaning);
	}
	else
	{
		return (delete_quotes_from_line(line));
	}
	return (res);
}
