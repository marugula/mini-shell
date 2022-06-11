/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_dllr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:02:16 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 14:47:29 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_var_dllr(char *tmp_line)
{
	int	i;

	i = 0;
	while (tmp_line[i] && (ft_isdigit(tmp_line[i]) == 1
			|| ft_isalpha(tmp_line[i]) == 1 || tmp_line[i] == '_'))
	{
		i++;
	}
	return (i);
}

char	*take_var_dllr(char *tmp_line)
{
	char	*var_dllr;
	int		i;

	if (tmp_line[0] == '?')
	{
		var_dllr = ft_strdup("?");
		if (!var_dllr)
			ft_errors_and_exit("check_dllr_line:", 0, ": malloc error.\n", FP);
		return (var_dllr);
	}
	i = len_of_var_dllr(tmp_line);
	var_dllr = ft_calloc(i + 1 + 1, sizeof(char));
	if (!var_dllr)
		ft_errors_and_exit("check_dllr_line:", 0, ": malloc error.\n", FP);
	i = 0;
	while (tmp_line[i] && (ft_isdigit(tmp_line[i]) == 1
			|| ft_isalpha(tmp_line[i]) == 1 || tmp_line[i] == '_'))
	{
		var_dllr[i] = tmp_line[i];
		i++;
	}
	var_dllr[i] = '=';
	var_dllr[i + 1] = '\0';
	return (var_dllr);
}

void	add_var_dllr_in_line(char *tmp_line, int *i, int *j, char **line)
{
	char	*var_dllr;
	char	*mean;

	*i = *i + *j;
	if (*i != *j)
		*line = conk_and_check(*line, (tmp_line + *j), (tmp_line + *i));
	if (tmp_line[*i + 1] && ft_isspace(tmp_line[*i + 1]) == 0)
	{
		var_dllr = take_var_dllr(&tmp_line[*i + 1]);
		mean = find_meaning_in_env(var_dllr, g_data.env, g_data.env_hide, 1);
		if (mean)
			*line = conk_and_check(*line, mean, (mean + ft_strlen(mean)));
		*j = *i + ft_strlen(var_dllr);
		if (var_dllr && var_dllr[0] == '?')
			*j = *j + 1;
		free(mean);
		mean = NULL;
		free(var_dllr);
	}
	else
	{
		*line = conk_and_check(*line, &tmp_line[*i], &tmp_line[*i + 1]);
		*j = *i + 1;
	}
}

char	*check_dllr_line(char *tmp_line, int flag_heredoc)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	line = NULL;
	while (tmp_line && tmp_line[j])
	{
		if (flag_heredoc == 1)
			i = is_dollar_in_line_heredoc(&tmp_line[j]);
		else
			i = is_dollar_in_line(&tmp_line[j]);
		if (i == -1)
		{
			line = conk_line(line, (tmp_line + j),
					(tmp_line + (j + ft_strlen(tmp_line + j))));
			if (!line)
				ft_errors_and_exit("check_dllr_line1:", 0, ": malloc.\n", FP);
			break ;
		}
		else
			add_var_dllr_in_line(tmp_line, &i, &j, &line);
	}
	free(tmp_line);
	return (line);
}
