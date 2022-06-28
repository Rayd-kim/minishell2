/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:33 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 21:21:48 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	error_stdin(char *str, int check)
{
	if (check == 1)
	{
		write (2, "bash: ", 6);
		write (2, str, ft_strlen(str));
		write (2, ": ", 2);
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		g_status = 127;
		exit (127);
	}
	else
	{
		write (2, "bash: ", 6);
		write (2, str, ft_strlen(str));
		write (2, ": ", 2);
		write (2, "command not found\n", 18);
		g_status = 127;
		exit (127);
	}
}

void	split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free (split);
}

int	check_quote(char *str, char **split, char *temp)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && double_q % 2 == 0)
			single_q++;
		else if (str[i] == '\"' && single_q % 2 == 0)
			double_q++;
		i++;
	}
	if (single_q % 2 == 0 && double_q % 2 == 0)
		return (0);
	else
	{
		split_free (split);
		free (temp);
		write (2, "Unclosed quotes\n", 16);
		return (1);
	}
}

int	check_pipe_close(char *str)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			arg = 0;
		else if (str[i] != ' ')
			arg++;
		i++;
	}
	if (arg == 0 && i != 0)
	{
		write (2, "Unclosed pipe\n", 14);
		free (str);
		return (1);
	}
	return (0);
}