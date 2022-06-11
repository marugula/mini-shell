/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:00:38 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/07 20:18:08 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_errors(char *str1, char *str2, char *str3, int flag_perror)
{
	write(2, "minishell: ", 11);
	if (str1)
	{
		write(2, str1, ft_strlen(str1));
	}
	if (flag_perror == FLAG_PERROR)
		perror(str2);
	else
	{
		if (str2)
			write(2, str2, ft_strlen(str2));
		if (str3)
			write(2, str3, ft_strlen(str3));
		else
			write(2, "Error.\n", 7);
	}
	return (1);
}

int	ft_errors_and_exit(char *str1, char *str2, char *str3, int flag_perror)
{
	write(2, "minishell: ", 11);
	if (str1)
		write(2, str1, ft_strlen(str1));
	if (flag_perror == FLAG_PERROR)
		perror(str2);
	else
	{
		if (str2)
			write(2, str2, ft_strlen(str2));
		if (str3)
			write(2, str3, ft_strlen(str3));
		else
			write(2, "Error.\n", 7);
	}
	if (errno != 0)
	{
		if (errno == 2)
			exit(127);
		if (errno == 13)
			exit(126);
		exit(errno);
	}
	else
		exit (1);
}

char	*ft_errors_returnnull(char *str1, char *str2,
		char *str3, int flag_perror)
{
	write(2, "minishell: ", 11);
	if (str1)
	{
		write(2, str1, ft_strlen(str1));
	}
	if (flag_perror == FLAG_PERROR)
		perror(str2);
	else
	{
		if (str2)
			write(2, str2, ft_strlen(str2));
		if (str3)
			write(2, str3, ft_strlen(str3));
		else
			write(2, "Error.\n", 7);
	}
	return (NULL);
}
