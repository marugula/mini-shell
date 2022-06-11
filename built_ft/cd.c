/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:09:38 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 12:56:43 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_null_write_errr(char *old_path);

char	*generate_new_path(char *old_path, char **env, int *n)
{
	char	*line_env;
	char	*new_path;

	if (!old_path || (old_path && old_path[0] == '~' && !old_path[1]))
		line_env = find_line_env(env, "HOME=", n);
	if (old_path && old_path[0] == '-' && !old_path[1])
		line_env = find_line_env(env, "OLDPWD=", n);
	*n = 7;
	if (!old_path || (old_path && old_path[0] == '~' && !old_path[1]))
		*n = 5;
	if (line_env == NULL)
		return (return_null_write_errr(old_path));
	new_path = ft_strdup(&(line_env)[*n]);
	if (!new_path)
		ft_errors_and_exit("cd", 0, ": malloc error.\n", FLAG_PERROR);
	return (new_path);
}

char	*check_path(char *old_path, char **env, int *n)
{
	char	*new_path;
	char	*line_env;
	int		indx;

	new_path = NULL;
	if (!old_path || ((old_path[0] == '-'
				|| old_path[0] == '~') && !old_path[1]))
		new_path = generate_new_path(old_path, env, n);
	else
	{
		if (old_path[0] == '~' && old_path[1] == '/')
		{
			line_env = find_line_env(env, "HOME=", &indx);
			if (line_env == NULL)
				return (ft_errors_returnnull(0, "cd", ": HOME not set.\n", 0));
			new_path = ft_strjoin(&(line_env)[5], &old_path[1]);
		}
		else
			new_path = old_path;
		if (access(new_path, F_OK) != 0)
			return (ft_errors_returnnull("cd: ", old_path, 0, FLAG_PERROR));
	}
	return (new_path);
}

char	**add_line_in_env(char **env, int *indx)
{
	int		i;
	int		count;
	char	**new;

	count = count_lines_env(env);
	if (count == 0)
		return (NULL);
	new = (char **) malloc(sizeof(char *) * (count + 1 + 1));
	if (!new)
		ft_errors_and_exit("add_line_in_env", 0, ": malloc error.\n", 0);
	new[count + 1] = NULL;
	i = 0;
	while (i < count - 1)
	{
		new[i] = env[i];
		i++;
	}
	new[i] = NULL;
	*indx = i;
	new[i + 1] = env[count - 1];
	return (new);
}

int	change_old_and_pwd(char ***env)
{
	char	*meaning_oldpwd;
	char	*meaning_pwd;
	char	*line_oldpwd;
	char	*line_pwd;

	meaning_oldpwd = find_meaning_in_env("PWD=", g_data.env, 0, 0);
	meaning_pwd = NULL;
	meaning_pwd = getcwd(meaning_pwd, PATH_MAX);
	if (meaning_pwd == NULL)
		return (ft_errors("cd: ", "getcwd", 0, FLAG_PERROR));
	line_pwd = ft_strjoin("PWD=", meaning_pwd);
	if (!line_pwd)
		ft_errors_and_exit("cd", 0, ": malloc error.\n", FLAG_PERROR);
	free(meaning_pwd);
	if (meaning_oldpwd)
	{
		line_oldpwd = ft_strjoin("OLDPWD=/", meaning_oldpwd);
		if (!line_oldpwd)
			ft_errors_and_exit("change_old_and_pwd",
				0, ": malloc error.\n", FLAG_PERROR);
		free(meaning_oldpwd);
		export_in_env(env, "OLDPWD=", line_oldpwd);
	}
	export_in_env(env, "PWD=", line_pwd);
	return (0);
}

int	ft_cd(char *old_path)
{
	char	*path;
	int		n;

	n = 0;
	path = check_path(old_path, g_data.env, &n);
	if (path == NULL)
		return (1);
	if (chdir(path) == -1)
		return (ft_errors("cd: ", path, 0, FLAG_PERROR));
	if (n == 7)
	{
		ft_putstr_fd(path, 1);
		write(1, "\n", 1);
	}
	if (path != old_path)
		free(path);
	if (change_old_and_pwd(&g_data.env) == 1)
		return (1);
	return (0);
}
