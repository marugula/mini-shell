/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:59:47 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 11:50:27 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILD_CARD_H
# define WILD_CARD_H

typedef struct s_part
{
	char			*line;
	struct s_part	*next;
}	t_part;

typedef struct s_quotes
{
	int		i;
	int		j;
	int		quotes;
	int		quotes2;
}	t_quotes;

char	*free_parts(t_part *first);
int		is_star_in_line(char *line);
t_part	*find_parts(char *line);
t_part	*find_meaning_star(t_part *first);
int		ft_strncmp_last(char *str1, char *str2, int len2);
t_part	*ft_free_mean(t_part **first);
void	set_dflt_t_quotes(t_quotes *inf);
char	**delete_quotes_from_line(char *line);

#endif
