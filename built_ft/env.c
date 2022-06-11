/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:02:14 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/05 15:16:39 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_lines_env(char **env)
{
	int	count;

	count = 0;
	if (env)
	{
		while (env[count])
		{
			count++;
		}
	}
	return (count);
}

char	*add_equal_sign(char *str)
{
	int		equal_sign;
	int		i;
	char	*new_str;

	equal_sign = 0;
	i = ft_strlen(str);
	if (str[i - 1] == '=')
		return (ft_strdup(str));
	new_str = NULL;
	new_str = ft_strjoin(str, "=");
	if (!new_str)
		ft_errors_and_exit("add_equal_sign:",
			0, ": malloc error.\n", FLAG_PERROR);
	return (new_str);
}

char	*find_line_env(char **env, char *origin_str, int *indx)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	str = add_equal_sign(origin_str);
	while (env[i])
	{
		n = ft_strncmp(env[i], str, ft_strlen(str));
		if (n == 0)
		{
			if (indx)
				*indx = i;
			free(str);
			return (env[i]);
		}
		i++;
	}
	free(str);
	return (NULL);
}

int	create_new_env(char ***new_env, char **env)
{
	char	**new;
	int		count;
	int		i;
	int		symb;

	count = count_lines_env(env);
	if (count == 0)
		return (ft_errors(0, "env", ": unseted.\n", 0));
	new = (char **) malloc(sizeof(char *) * (count + 1));
	if (!new)
		ft_errors_and_exit("new_env:", 0, ": malloc error.\n", FLAG_PERROR);
	new[count] = NULL;
	i = 0;
	while (i < count)
	{
		symb = ft_strlen(env[i]);
		new[i] = (char *) malloc (sizeof(char) * (symb + 1));
		if (!new[i])
			ft_errors_and_exit("create_new_env:",
				0, ": malloc error.\n", FLAG_PERROR);
		new[i] = ft_memcpy(new[i], env[i], symb + 1);
		i++;
	}
	*new_env = new;
	return (0);
}

char	**delete_line_env(char **env, int indx)
{
	int		count;
	char	**new;
	int		i;
	int		j;

	count = count_lines_env(env);
	if (count == 0)
		return (NULL);
	new = (char **) malloc(sizeof(char *) * (count));
	if (!new)
		ft_errors_and_exit("env:", 0, ": malloc error.\n", FLAG_PERROR);
	new[count - 1] = NULL;
	i = 0;
	j = 0;
	while (i < count - 1)
	{
		if (j != indx)
		{
			new[i] = env[j];
			i++;
		}
		j++;
	}
	return (new);
}
