/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dllr_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:44:16 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 14:50:36 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*conk_and_check(char *dest, char *start, char *end)
{
	char	*line;

	line = conk_line(dest, start, end);
	if (!line)
		ft_errors_and_exit("conk_line:", 0, ": malloc error.\n", FP);
	return (line);
}

int	is_dollar_in_line(char *tmp_line)
{
	int	i;
	int	quote;
	int	quote2;

	i = 0;
	quote = 0;
	quote2 = 0;
	while (tmp_line[i])
	{
		if (tmp_line[i] == '\'' && quote2 % 2 == 0)
			quote++;
		if (tmp_line[i] == '"')
			quote2++;
		if (tmp_line[i] == '$' && quote % 2 == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_dollar_in_line_heredoc(char *tmp_line)
{
	int	i;

	i = 0;
	while (tmp_line[i])
	{
		if (tmp_line[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin_and_symb(char *s1, char *s2, char symb)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = symb;
	str[ft_strlen(s1) + ft_strlen(s2) + 1] = '\0';
	free(s1);
	return (str);
}
