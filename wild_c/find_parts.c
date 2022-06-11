/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_parts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:03:34 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 16:04:06 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "wild_card.h"

char	*free_parts(t_part *first)
{
	t_part	*parts;
	t_part	*tmp;

	parts = first ;
	while (parts)
	{
		tmp = parts;
		parts = parts->next;
		free(tmp->line);
		free(tmp);
	}
	return (0);
}

int	is_star_in_line(char *line)
{
	int			i;
	static int	quote11;
	static int	quote22;

	i = 0;
	while (line && line[i])
	{
		if ((line[i] == '*' && i > 0 && quote11 % 2 == 0 && quote22 % 2 == 0)
			|| (line[i] == '*' && i == 0))
			return (i);
		if (line[i] == '\'' && quote22 % 2 == 0)
			quote11 += 1;
		if (line[i] == '"' && quote11 % 2 == 0)
			quote22 += 1;
		i++;
	}
	return (-1);
}

void	split_line(char *line, int i, t_part *parts)
{
	int		len;

	while (line[i])
	{
		len = is_star_in_line(line + i);
		if (len == -1)
		{
			parts->line = ft_strdupl((line + i), ft_strlen((line + i)));
			if (!parts->line)
				ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FP);
			return ;
		}
		else if (i == 0 && len == 0)
			parts->line = NULL;
		else if (len != 0)
			parts->line = ft_strdupl((line + i), len);
		parts->next = (t_part *) ft_calloc (1, sizeof(t_part));
		if (!parts->next)
			ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FP);
		parts = parts->next;
		i = len + i + 1;
	}
}

t_part	*find_parts(char *line)
{
	t_part	*parts;
	t_part	*first;
	int		i;

	parts = (t_part *) ft_calloc (1, sizeof(t_part));
	if (!parts)
		ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FLAG_PERROR);
	first = parts;
	i = 0;
	split_line(line, i, parts);
	return (first);
}
