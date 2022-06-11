/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:52:06 by marugula          #+#    #+#             */
/*   Updated: 2022/06/09 10:16:29 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strdupl(char *str, size_t len)
{
	char	*newstr;
	size_t	i;

	if (ft_strlen(str) < len)
		len = ft_strlen(str);
	newstr = ft_calloc(len + 1, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstr[i] = str[i];
		i++;
	}
	return (newstr);
}

char	*conk_line(char *dest, char *start, char *end)
{
	char	*rez_line;
	char	*tmp;

	if (start == NULL || end == NULL)
		return (dest);
	if (end - start <= 0)
		return (dest);
	rez_line = ft_strdupl(start, end - start);
	if (rez_line == NULL)
		return (ft_free(dest));
	if (dest != NULL)
	{
		tmp = rez_line;
		rez_line = ft_strjoin(dest, rez_line);
		free (tmp);
		if (rez_line == NULL)
			return (ft_free(dest));
	}
	free(dest);
	return (rez_line);
}

char	*find_next_quatation_mark(char	*first_mark_p)
{
	char	*next_mark_p;

	next_mark_p = first_mark_p + 1;
	while (*next_mark_p && *next_mark_p != *first_mark_p)
	{
		if (next_mark_p == NULL)
			return (NULL);
		next_mark_p++;
	}
	if (*next_mark_p == 0)
	{
		g_data.our_errno = ERROR_QMFIND;
		return (NULL);
	}
	else
		return (next_mark_p);
}

int	open_file(char *curent_p, int mod)
{
	char	*name_file;
	int		size_name;
	int		fd;

	size_name = ft_strlen(curent_p);
	if (size_name < 0)
	{
		g_data.our_errno = ERROR_QMFIND;
		return (-1);
	}
	name_file = ft_strdupl(curent_p, size_name);
	if (name_file == NULL)
		return (-1);
	fd = open(name_file, mod, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		ft_errors(NULL, name_file, NULL, FLAG_PERROR);
	free(name_file);
	return (fd);
}

int	fill_default_val(t_exec_cmds *cmds)
{
	cmds->fd_dest = -1;
	cmds->fd_from = -1;
	cmds->flag_dest = 0;
	cmds->flag_from = 0;
	return (0);
}
