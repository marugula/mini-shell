/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_c_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:02:33 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 11:55:43 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "wild_card.h"

int	ft_strncmp_last(char *str1, char *str2, int len2)
{
	int	len1;

	len1 = ft_strlen(str1) - 1;
	len2 = len2 - 1;
	if (len1 >= len2)
	{
		while (len2 >= 0)
		{
			if (str1[len1] != str2[len2])
				return (str1[len1] - str2[len2]);
			len1--;
			len2--;
		}
		return (0);
	}
	else
	{
		return (-1);
	}
	return (0);
}

t_part	*ft_free_mean(t_part **first)
{
	free_parts(*first);
	*first = NULL;
	return (NULL);
}

void	set_dflt_t_quotes(t_quotes *inf)
{
	inf->quotes = 0;
	inf->quotes2 = 0;
	inf->i = 0;
	inf->j = 0;
}
