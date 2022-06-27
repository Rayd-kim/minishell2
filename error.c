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
int	status;
void	error_stdin(char *str)
{
	write (2, "bash: ", 6);
	write (2, str, ft_strlen(str));
	write (2, ": ", 2);
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
	status = errno;
	exit (errno);
}

void	split_free(char **split)
{
	int	i = 0;

	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free (split);
}

int	check_quote(char *str)
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
		write (2, "Unclosed quotes\n", 16);
		return (1);
	}
}