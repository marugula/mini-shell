/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:59:14 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 15:26:23 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*clear_arg_arr(char **arg)
{
	int	i;

	i = 0;
	if (arg != NULL)
	{
		while (arg[i] != 0)
		{
			free(arg[i]);
			i++;
		}
		free(arg);
	}
	return (NULL);
}

void	*clear_word_lst(t_words_lst *lst)
{
	t_words_lst	*temp;

	while (lst != NULL)
	{
		if (lst->content != NULL)
			free(lst->content);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
	return (NULL);
}

void	*ft_free(void *p)
{
	if (p != NULL)
		free(p);
	return (NULL);
}

void	close_opened_file(t_exec_cmds *cmds)
{
	if (cmds->fd_dest > 2)
		close(cmds->fd_dest);
	if (cmds->fd_from > 2)
		close(cmds->fd_from);
	if (access(".heredoc", F_OK) == 0)
		unlink_heredoc_fd();
}

void	*clear_exec_cmds(t_exec_cmds *cmds)
{
	int			i;
	t_exec_cmds	*temp;

	while (cmds != NULL)
	{
		i = 0;
		if (cmds->args != NULL)
		{
			while (cmds->args[i] != NULL)
			{
				free(cmds->args[i]);
				i++;
			}
			free(cmds->args);
		}
		close_opened_file(cmds);
		temp = cmds;
		cmds = cmds->next;
		free(temp);
	}
	return (NULL);
}
