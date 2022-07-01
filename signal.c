/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:11:00 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 15:11:01 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void	kill_process(int *process)
{
	pid_t	pid;
	int		check;

	*process = 0;
	while (1)
	{
		pid = waitpid(0, &check, WNOHANG);
		if (pid != -1)
		{
			*process += 1;
			kill (pid, SIGQUIT);
		}
		else
			break ;
	}
}

void	signal_handler(int sig)
{
	int		process;

	kill_process(&process);
	if (sig == CTRL_C && g_vari.flag == 1 && process == 0)
	{
		g_vari.status = 130;
		g_vari.flag = dup(0);
		write (1, ">  \n", 4);
		close(0);
	}
	else if (sig == CTRL_C && process == 0)
	{
		g_vari.status = 1;
		rl_on_new_line();
		rl_redisplay();
		write (1, "  \n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == CTRL_C && process != 0)
	{
		g_vari.status = 130;
		write (1, "\n", 1);
	}
}

void	set_signal(void)
{
	signal (CTRL_C, signal_handler);
	signal (CTRL_SLASH, SIG_IGN);
}
