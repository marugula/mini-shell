/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:27:41 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 12:28:24 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

void	clearsplit(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*strjoin3(char *str1, char *str2, char *str3)
{
	char	*rez;
	char	*tmp;

	rez = ft_strjoin(str1, str2);
	if (rez == 0)
		return (0);
	tmp = rez;
	rez = ft_strjoin(rez, str3);
	free(tmp);
	if (rez == 0)
		return (0);
	else
		return (rez);
}

void	back_to_dflt_signl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	g_data.consol_ignore.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &g_data.consol_ignore);
}

char	*check_in_allpath(char **allpath, char *cmdarg)
{
	char	*pathcmd;

	while (allpath && *allpath)
	{
		pathcmd = strjoin3(*allpath, "/", cmdarg);
		if (!pathcmd)
			ft_errors_and_exit("path:", 0, ": malloc.\n", FP);
		if (access(pathcmd, X_OK) == 0)
			return (pathcmd);
		free(pathcmd);
		allpath++;
	}
	return (NULL);
}
