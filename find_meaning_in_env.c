/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_meaning_in_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:02:36 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 18:05:25 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clip_meaning_line(char *meaning_line, char *var_dllr, int flag_equal)
{
	char	*meaning;
	int		count_line;
	int		count_var;
	int		i;

	count_var = ft_strlen(var_dllr);
	count_line = ft_strlen(meaning_line);
	meaning = ft_calloc(count_line - count_var + 1, sizeof(char));
	if (!meaning)
		ft_errors_and_exit("clip line", 0, ": malloc error.\n", FLAG_PERROR);
	i = 0;
	if (flag_equal == 0)
		count_var++;
	while (meaning_line[count_var])
		meaning[i++] = meaning_line[count_var++];
	return (meaning);
}

char	*mean_from_env(char *var_dllr, char **env, int flag_equal)
{
	char	*mean1;
	char	*line;

	mean1 = NULL;
	line = find_line_env(env, var_dllr, 0);
	if (line)
		mean1 = clip_meaning_line(line, var_dllr, flag_equal);
	return (mean1);
}

char	*find_meaning_in_env(char *var_dllr, char **env,
	char **env2, int flag_equal)
{
	char	*meaning;

	meaning = NULL;
	if (!var_dllr)
		return (NULL);
	if (var_dllr[0] == '?')
	{
		meaning = ft_itoa(g_data.our_errno);
		if (!meaning)
			ft_errors_and_exit("find mean env", 0, ": malloc error.\n", FP);
	}
	if (var_dllr[0] == '0' && meaning == NULL)
	{
		meaning = ft_strdup("Myshell");
		if (!meaning)
			ft_errors_and_exit("find mean env", 0, ": malloc error.\n", FP);
	}
	if (env && meaning == NULL)
		meaning = mean_from_env(var_dllr, env, flag_equal);
	if (env2 && meaning == NULL)
		meaning = mean_from_env(var_dllr, env2, flag_equal);
	return (meaning);
}
