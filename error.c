/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:33 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:03:35 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_stdin(char *str)
{
	write (2, "bash: ", 6);
	write (2, str, ft_strlen(str));
	write (2, ": ", 2);
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
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
