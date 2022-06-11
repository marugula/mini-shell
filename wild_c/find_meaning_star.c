/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_meaning_star.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:59:51 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 17:47:48 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "wild_card.h"

int	checking_one_part(t_part *first, char *line, int *i, int flag)
{
	int	res_cmp;

	if (flag == 1)
	{
		if (first && first->line != NULL)
		{
			if (ft_memcmp(line, first->line, ft_strlen(first->line)) != 0)
				return (-1);
			*i = ft_strlen(first->line);
		}
	}
	if (flag == 2)
	{
		if (first && first->line != NULL)
		{
			res_cmp = ft_strncmp_last((line + *i), first->line,
					ft_strlen(first->line));
			if (res_cmp != 0)
				return (-1);
		}
	}
	return (0);
}

int	checking_mid_parts(t_part *parts, t_part *last_p, char *line, int *i)
{
	int	res_cmp;

	while (parts && parts != last_p)
	{
		if (parts->line)
		{
			res_cmp = -1;
			while (line[*i])
			{
				res_cmp = ft_memcmp((line + *i), parts->line,
						ft_strlen(parts->line));
				*i = *i + 1;
				if (res_cmp == 0)
					break ;
			}
			if (res_cmp != 0)
				return (-1);
		}
		parts = parts->next;
	}
	return (0);
}

int	check_meaning_star(t_part *first, char *line)
{
	t_part	*parts;
	t_part	*last_p;
	int		i;

	parts = first->next;
	last_p = first->next;
	while (last_p->next)
		last_p = last_p->next;
	i = 0;
	if ((first->line && first->line[0] != '.') || first->line == NULL)
	{
		if (ft_memcmp(line, ".", 1) == 0)
			return (-1);
	}
	if (checking_one_part(first, line, &i, 1) == -1)
		return (-1);
	if (checking_mid_parts(parts, last_p, line, &i) == -1)
		return (-1);
	if (checking_one_part(last_p, line, &i, 2) == -1)
		return (-1);
	return (0);
}

void	cycle_through_files(DIR *direct, struct dirent *diren,
	t_part **mean, t_part *first)
{
	t_part			*f_mean;

	f_mean = *mean;
	while (diren != NULL)
	{
		if (check_meaning_star(first, diren->d_name) == 0)
		{
			(*mean)->line = ft_strdup(diren->d_name);
			if (!(*mean)->line)
				ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FP);
			(*mean)->next = ft_calloc(sizeof(t_part), 1);
			if (!(*mean)->next)
				ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FP);
			*mean = (*mean)->next;
		}
		diren = readdir(direct);
	}
}

t_part	*find_meaning_star(t_part *first)
{
	char			*dir;
	DIR				*direct;
	struct dirent	*diren;
	t_part			*mean;
	t_part			*f_mean;

	dir = NULL;
	dir = getcwd(dir, PATH_MAX);
	if (dir == NULL)
		return (NULL);
	direct = opendir(dir);
	free(dir);
	mean = (t_part *) ft_calloc(sizeof(t_part), 1);
	f_mean = mean;
	if (!mean || !direct)
		ft_errors_and_exit("wild_cards:", 0, ": malloc error.\n", FLAG_PERROR);
	diren = readdir(direct);
	cycle_through_files(direct, diren, &mean, first);
	if (f_mean->line == NULL && f_mean->next == NULL)
		ft_free_mean(&f_mean);
	if (closedir(direct) == -1)
		return (NULL);
	return (f_mean);
}
