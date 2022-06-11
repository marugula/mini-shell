/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_is_who.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:41:40 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 15:27:53 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' \
	|| c == '\v' || c == '\f' \
	|| c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	is_log_operator(char	*curent_p)
{
	if (*curent_p == PIPE)
		return (PIPE);
	return (NOTLOGOP);
}

int	is_redir_op(char	*curent_p)
{
	if (curent_p == NULL)
		return (NOTREDIR);
	if (ft_strncmp(curent_p, ">>", 2) == 0)
		return (REDIROUTAP);
	else if (ft_strncmp(curent_p, ">", 1) == 0)
		return (REDIROUT);
	else if (ft_strncmp(curent_p, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(curent_p, "<", 1) == 0)
		return (REDIRIN);
	else
		return (NOTREDIR);
}

int	is_spec_symb(char *curent_p)
{
	if (*curent_p == SINGLEQM)
		return (SINGLEQM);
	if (*curent_p == DOUBLEQM)
		return (DOUBLEQM);
	if (*curent_p == DOLAR)
		return (DOLAR);
	if (*curent_p == STAR)
		return (STAR);
	if (*curent_p == SLASH)
		return (SLASH);
	else
		return (NOTSPEC);
}

int	is_token(char *curent_p)
{
	if (*curent_p == PIPE)
		return (PIPE);
	if (*curent_p == '>' && *(curent_p + 1) != '>')
		return (REDIROUT);
	if (*curent_p == '<' && *(curent_p + 1) != '<')
		return (REDIRIN);
	if (*curent_p == '>' && *(curent_p + 1) == '>')
		return (REDIROUTAP);
	if (*curent_p == '<' && *(curent_p + 1) == '<')
		return (HEREDOC);
	return (ISWORD);
}
