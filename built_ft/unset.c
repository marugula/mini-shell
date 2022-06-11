/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:12:17 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/04 16:12:20 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(char *str, char ***env)
{
	char	*this_str;
	char	**env_tmp;
	char	**new_env;
	int		indx;

	if (!str)
		return (ft_errors(0, "unset:", "not enough arguments.\n", 0));
	this_str = find_line_env((*env), str, &indx);
	if ((!this_str))
		return (0);
	new_env = delete_line_env((*env), indx);
	if (!new_env)
		return (ft_errors(0, "unset", ": Error malloc.\n", 0));
	env_tmp = (*env);
	(*env) = new_env;
	free(env_tmp);
	free(this_str);
	return (0);
}

int	ft_unset(char *str, char ***env, char ***second_env)
{
	int	rez;

	rez = 0;
	if (env)
	{
		rez = unset(str, env);
	}
	if (second_env)
	{
		rez = unset(str, second_env);
	}
	return (rez);
}
