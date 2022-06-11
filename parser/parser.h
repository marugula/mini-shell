/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:29:06 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 16:37:29 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* parser_proc_redirect.c */
int			proc_redir(t_exec_cmds *data, t_words_lst **words);
int			proc_redirout(t_exec_cmds *data, t_words_lst **words, int mod);
int			proc_redirin(t_exec_cmds *data, t_words_lst **words);
int			proc_heredoc(t_exec_cmds *data, t_words_lst **words);
int			make_heredoc(char *stop);

/* parser_exec_data_creat.c */
int			proc_pipe(t_exec_cmds **data);
int			proc_word(t_exec_cmds *data, t_words_lst *word);

/* parser_exec_data_utils.c */
char		**mass_strjoin(char **first, char **second);
int			mass_strlen(char **lines);
int			next_pipe_and_clear(char *text, t_words_lst **words, \
												t_exec_cmds *data);
int			proc_wildcard(char **content);

/* parser_word_list_creat.c */
char		*skip_isspace(char *curent_p);
t_words_lst	*creat_word_list(char *line);

/* parser_clear.c */
void		*clear_word_lst(t_words_lst *lst);
void		*ft_free(void *p);
void		close_opened_file(t_exec_cmds *cmds);
void		*clear_arg_arr(char **arg);

/* parser_is_who.c */
int			is_brace(char	*curent_p);
int			is_log_operator(char	*curent_p);
int			is_redir_op(char	*curent_p);
int			is_spec_symb(char *curent_p);
int			is_token(char *curent_p);

/* parser_word_list_utils.c*/
char		*end_of_word(char	*curent_p);
char		*next_word(char	*curent_p);
t_words_lst	*add_word_to_end_line(t_words_lst *head, char *word, int is_who);
t_words_lst	*new_word_lst(void);
t_words_lst	*find_next_pipe(t_words_lst *curent_word);

/* parser_utils.c */
char		*find_next_quatation_mark(char	*first_mark_p);
int			open_file(char *curent_p, int mod);
int			fill_default_val(t_exec_cmds *cmds);

#endif