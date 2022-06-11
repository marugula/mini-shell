/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamchoor <tamchoor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:55:29 by marugula          #+#    #+#             */
/*   Updated: 2022/06/07 20:28:41 by tamchoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# include <limits.h>
# include <dirent.h>

# include "libft/libft.h"
# include <termios.h>

typedef struct s_global_var
{
	int				our_errno;
	char			**env;
	char			**env_hide;
	struct termios	consol_ignore;
}	t_data;

t_data	g_data;

/* marugula changes  */

/* defines for main cmds*/
# define END_STR	0
# define CONTINUE	1
# define STD_ERROR	-1

/* defines for cmds tree */
# define ENDLINE	-1
# define NOTOPER	0

# define NOTLOGOP	0
# define NOTBRACE	0
# define ANDAND		1
# define OROR		2
# define OPENBRACE	3
# define CLOSEBRACE 4
# define COSTIL		5

# define ISCASE		1
# define ISNOTCASE	0

# define NOTSPEC	0
# define DOUBLEQM	'"'
# define SINGLEQM	'\''
# define PIPE		'|'
# define SEMICON	';'
# define DOLAR		'$'
# define STAR		'*'
# define SLASH		'\\'

# define ISWORD		0

# define NOTREDIR	0
/* > */
# define REDIROUT	10

/* >> */
# define REDIROUTAP	11

/* < */
# define REDIRIN	12

/* << */
# define HEREDOC	13

# define IN_NOTHEREDOC	0
# define IN_HEREDOC		1

/* малок косякнул */
# define ERROR_MALLOC		1

/* не найденная парная ковычка */
# define ERROR_QMFIND		2

/* не найдены аргументы или не коректный оператор */
# define ERROR_UNEXPOP		2

# define ERROR_HEREDOC		10

# define ERROR_OPEN			11

# define ERORR_NO_FILENAME	12

typedef struct s_line_in_word_lst
{
	char						*content;
	int							is_who;
	struct s_line_in_word_lst	*next;
	struct s_line_in_word_lst	*prev;
}	t_words_lst;

typedef struct s_with_pipe_and_args
{
	char						**args;
	int							fd_dest;
	int							fd_from;
	int							flag_dest;
	int							flag_from;
	struct s_with_pipe_and_args	*next;
	struct s_with_pipe_and_args	*prev;
}	t_exec_cmds;

/* parser.c */
t_exec_cmds	*parser(char	*line);

/* parser_exec_data_creat.c */
t_exec_cmds	*creat_exec_data(t_words_lst *words);

/* parser_utils.c */
char		*conk_line(char *dest, char *start, char *end);
char		*ft_strdupl(char *str, size_t len);

/* parser_syntax_check.c */
char		*check_syntax(t_words_lst *head);

/* parser_clear.c */
void		*clear_exec_cmds(t_exec_cmds *cmds);

/* parser_is_who.c */
int			ft_isspace(char c);

char		*take_var_dllr(char *tmp_line);
void		start_heredoc(char *current_p);
char		*find_meaning_in_env(char *var_dllr, char **env, char **env2, \
														int flag_equal);
char		*check_dllr_line(char *tmp_line, int flag_heredoc);

void		unlink_heredoc_fd(void);

# define CD				11
# define ENV			12
# define PWD			13
# define UNSET			14
# define EXPORT			15
# define ECHO_CMD		16
# define EXIT			17
# define EQUAL			18
# define FLAG_PERROR	19
# define FP				FLAG_PERROR

int			status_of_process(int status);
int			open_heredoc_fd(void);

int			create_new_env(char ***new_env, char **env);
int			printf_env(char **env, int fd);
char		**add_line_in_env(char **env, int *indx);
int			count_lines_env(char **env);
int			change_oldpwd(char ***env);
int			add_new_shlvl(char ***env);
int			unset(char *str, char ***env);
char		**delete_line_env(char **env, int indx);
int			ft_errors(char *str1, char *str2, char *str3, int flag_perror);
int			export(char *new_line, char ***env);
char		*conk_and_check(char *dest, char *start, char *end);
int			is_dollar_in_line(char *tmp_line);
int			is_dollar_in_line_heredoc(char *tmp_line);

int			ft_pwd(int fd);
int			ft_exit(char **lines, int flag, int flag_pipex);
int			ft_errors_and_exit(char *str1, char *str2, char *str3, \
													int flag_perror);

long		ft_atol(const char *str);

char		*find_line_env(char **env, char *str, int *indx);

char		**wild_cards(char *line);
char		*ft_strjoin_and_symb(char *s1, char *s2, char symb);

int			executer(t_exec_cmds *cmds);

char		*ft_errors_returnnull(char *str1, char *str2, char *str3, \
														int flag_perror);

int			export_in_env(char ***env, char *first_part, char *line_for_exprt);
int			ft_cd(char *old_path);

void		rl_replace_line(char *str, int n);
void		signal_handler2(int sig);

#endif
