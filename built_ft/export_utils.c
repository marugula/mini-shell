/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:33:56 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 20:52:25 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strlen_find_signs_and_check(int *equal_sign, int *plus_sign, char *new_line)
{
	int		count;
	char	*line;

	line = new_line;
	count = 0;
	*equal_sign = 0;
	*plus_sign = 0;
	while (line[count])
	{
		if (line[count] == '+' && line[count + 1] == '=' && *equal_sign == 0)
			*plus_sign = count;
		else if (line[count] == '=' && *equal_sign == 0)
			*equal_sign = count;
		else if ((line[count] != '=' && line[count] != '_'
				&& ft_isalpha(line[count]) != 1 && ft_isdigit(line[count]) != 1)
			&& *equal_sign == 0)
			return (-1);
		count++;
	}
	return (count);
}

char	*prepair_line_with_plus(int *equal_sign,
	int *plus_sign, char *new_line)
{
	char	*line_for_exprt;
	char	*meaning;
	char	*first_part;

	first_part = ft_strdupl(new_line, *plus_sign);
	if (!first_part)
		ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
	meaning = find_meaning_in_env(first_part,
			g_data.env, g_data.env_hide, 1);
	line_for_exprt = ft_strjoin(first_part, meaning);
	if (!line_for_exprt)
		ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
	free(meaning);
	free(first_part);
	line_for_exprt = conk_line(line_for_exprt, &new_line[*equal_sign + 1],
			&new_line[ft_strlen(new_line)]);
	if (!line_for_exprt)
		ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
	return (line_for_exprt);
}

char	*prepair_line_for_export(int *equal_sign,
	int *plus_sign, char *new_line)
{
	char	*line_for_exprt;
	char	*meaning;

	if (*equal_sign == 0)
	{
		meaning = find_meaning_in_env(new_line, g_data.env, g_data.env_hide, 1);
		if (!meaning)
			return (NULL);
		line_for_exprt = ft_strjoin(new_line, meaning);
		if (!line_for_exprt)
			ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
		free(meaning);
		return (line_for_exprt);
	}
	else if (*plus_sign != 0)
		line_for_exprt = prepair_line_with_plus(equal_sign,
				plus_sign, new_line);
	else
	{
		line_for_exprt = ft_strdup(new_line);
		if (!line_for_exprt)
			ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
	}
	return (line_for_exprt);
}

int	check_str_for_export(char *new_line, int *equal_sign,
	int *plus_sign, char **line_for_exprt)
{
	int		count;

	if (ft_isalpha(new_line[0]) != 1 && new_line[0] != '_' )
		return (ft_errors("export ", new_line,
				": not a valid identifier.\n", 0));
	count = strlen_find_signs_and_check(equal_sign, plus_sign, new_line);
	if (count == -1)
		return (ft_errors("export ", new_line,
				": c not a valid identifier.\n", 0));
	*line_for_exprt = prepair_line_for_export(equal_sign, plus_sign, new_line);
	return (0);
}

char	*return_null_write_errr(char *old_path)
{
	if (!old_path || (old_path && old_path[0] == '~' && !old_path[1]))
		return (ft_errors_returnnull(0, "cd", ": HOME not set.\n", 0));
	else
		return (ft_errors_returnnull(0, "cd", ": OLDPWD not set.\n", 0));
}
