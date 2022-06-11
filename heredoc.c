/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 13:04:02 by tamchoor          #+#    #+#             */
/*   Updated: 2022/06/09 10:52:12 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_stop_word(char *current_p, size_t *stop_w_len)
{
	char	*stop_word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isspace(current_p[j]) == 1)
		j++;
	while (current_p[j + i] && ft_isspace(current_p[j + i]) == 0)
		i++;
	stop_word = ft_strdupl((current_p + j), i);
	if (!stop_word)
		ft_errors_and_exit("take_stop_word:", current_p, " error.\n", FP);
	*stop_w_len = i;
	return (stop_word);
}

char	*start_reading_heredoc(char *stop_word)
{
	char	*tmp_line;
	size_t	stop_w_len;
	char	*heredoc_line;

	stop_w_len = ft_strlen(stop_word);
	heredoc_line = NULL;
	while (1)
	{
		tmp_line = readline("> ");
		if (!tmp_line || tmp_line[0] == '\0'
			|| (ft_strlen(tmp_line) == stop_w_len
				&& ft_memcmp(tmp_line, stop_word, stop_w_len) == 0))
			break ;
		tmp_line = check_dllr_line(tmp_line, IN_HEREDOC);
		heredoc_line = ft_strjoin_and_symb(heredoc_line, tmp_line, '\n');
		free(tmp_line);
		if (!heredoc_line)
			ft_errors_and_exit("take_stop_word:", stop_word, " error.\n", FP);
	}
	if (tmp_line)
		free(tmp_line);
	return (heredoc_line);
}

void	start_heredoc(char *stop_word)
{
	char	*heredoc_line;
	int		fd;

	signal(SIGINT, SIG_DFL);
	heredoc_line = start_reading_heredoc(stop_word);
	if (heredoc_line == NULL)
		heredoc_line = ft_calloc(1, sizeof(char));
	if (!heredoc_line)
		ft_errors_and_exit("take_stop_word:", stop_word, " error.\n", FP);
	fd = open(".heredoc", O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		ft_errors_and_exit("heredoc open:", stop_word, " error.\n", FP);
	write (fd, heredoc_line, ft_strlen(heredoc_line));
	close(fd);
	exit(0);
}

int	open_heredoc_fd(void)
{
	int	fd;

	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		ft_errors_and_exit("heredoc open:", 0, " error.\n", FP);
	}
	return (fd);
}

void	unlink_heredoc_fd(void)
{
	int	res;

	res = unlink(".heredoc");
	if (res == -1)
		ft_errors(".heredoc", 0, ": unlink error.\n", FLAG_PERROR);
}
