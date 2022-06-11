/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:02:26 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 19:49:48 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_str_for_export(char *new_line, int *equal_sign,
		int *plus_sign, char **line_for_exprt);

int	print_export(int fd)
{
	int	count;
	int	count_symb;
	int	symb;

	count = 0;
	count_symb = 0;
	while (g_data.env[count])
	{
		symb = 0;
		while (g_data.env[count][symb])
			symb++;
		write (fd, "declare -x ", 11);
		write (fd, g_data.env[count], symb);
		write (fd, "\n", 1);
		count++;
		count_symb += symb;
	}
	return (0);
}

char	*find_first_part(char *new_line, int equal_sign, int plus_sign)
{
	char	*first_part;

	if (equal_sign == 0)
		first_part = ft_strdup(new_line);
	else if (plus_sign != 0)
		first_part = ft_strdupl(new_line, plus_sign);
	else
		first_part = ft_strdupl(new_line, equal_sign);
	if (!first_part)
		ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
	return (first_part);
}

int	export_in_env(char ***env, char *first_part, char *line_for_exprt)
{
	int		indx;
	char	*line_in_env;
	char	**new_env;
	char	**env_tmp;

	indx = 0;
	line_in_env = find_line_env(*env, first_part, &indx);
	if (!line_in_env)
	{
		new_env = add_line_in_env((*env), &indx);
		if (!new_env)
			ft_errors_and_exit("export:", 0, ": malloc error.\n", FLAG_PERROR);
		new_env[indx] = line_for_exprt;
		env_tmp = (*env);
		*env = new_env;
		(*env) = new_env;
		env = &new_env;
		free(env_tmp);
	}
	else
	{
		(*env)[indx] = line_for_exprt;
	}
	free(line_in_env);
	return (0);
}

int	export(char *new_line, char ***env)
{
	int		equal_sign;
	int		plus_sign;
	char	*line_for_exprt;
	char	*first_part;

	if (!new_line)
		return (print_export(1));
	line_for_exprt = NULL;
	if (check_str_for_export(new_line, &equal_sign,
			&plus_sign, &line_for_exprt) == 1)
		equal_sign = 0;
	first_part = find_first_part(new_line, equal_sign, plus_sign);
	if (!line_for_exprt && *env == g_data.env)
		export_in_env(&g_data.env, first_part, ft_strjoin(first_part, "="));
	else if (line_for_exprt)
		export_in_env(env, first_part, line_for_exprt);
	free(first_part);
	return (0);
}

int	export_in_hide(char *new_line)
{
	int		equal_sign;
	int		plus_sign;
	char	*line_for_exprt;
	char	*first_part;
	char	*line_in_env;

	if (!new_line)
		return (print_export(1));
	line_for_exprt = NULL;
	if (check_str_for_export(new_line, &equal_sign,
			&plus_sign, &line_for_exprt) == 1)
		equal_sign = 0;
	first_part = find_first_part(new_line, equal_sign, plus_sign);
	line_in_env = find_line_env(g_data.env, first_part, &equal_sign);
	if (line_in_env)
	{
		export_in_env(&g_data.env, first_part, line_for_exprt);
	}
	else
	{
		export_in_env(&g_data.env_hide, first_part, line_for_exprt);
	}
	free(first_part);
	return (0);
}
