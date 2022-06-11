/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marugula <marugula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:11:21 by marugula          #+#    #+#             */
/*   Updated: 2022/06/11 09:14:17 by marugula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void )sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	change_signals(void)
{
	g_data.consol_ignore.c_lflag &= ~ECHOCTL;
	signal(SIGQUIT, SIG_IGN);
	signal (SIGINT, signal_handler);
	tcsetattr(0, TCSANOW, &g_data.consol_ignore);
}

int	set_new_env(char **env)
{
	g_data.env = NULL;
	if (create_new_env(&g_data.env, env) == 1
		|| create_new_env(&g_data.env_hide, env) == 1
		|| add_new_shlvl(&g_data.env) == 1
		|| unset("OLDPWD=", &g_data.env) == 1
		|| unset("SHELL=", &g_data.env) == 1
		|| export("SHELL=Myshell😉", &g_data.env))
		return (1);
	tcgetattr(0, &g_data.consol_ignore);
	return (0);
}

void	minishell(void)
{
	char		*str;
	t_exec_cmds	*lst;

	while (1)
	{
		str = NULL;
		change_signals();
		errno = 0;
		str = readline("Myshell😉 $ ");
		if (!str)
			ft_exit(NULL, 0, 0);
		add_history(str);
		lst = parser(str);
		if (!lst)
		{
			free(str);
			continue ;
		}
		executer(lst);
		clear_exec_cmds(lst);
		free(str);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	if (set_new_env(env) == 1)
		return (1);
	g_data.our_errno = 0;
	minishell();
	return (1);
}
