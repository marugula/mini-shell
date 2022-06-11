/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:46:00 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 11:19:04 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	status_of_process(int status)
{
	int	rez;

	if (WIFEXITED(status))
		rez = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			write(2, "\b\b\b\b\b\b\b\b\b\b\b\b", 12);
			rez = 130;
		}
		if (WTERMSIG(status) == 3)
		{
			ft_putstr_fd("Myshell : Quit: 3\n", 2);
			rez = 131;
		}
	}
	else
	{
		rez = 0;
	}
	return (rez);
}
