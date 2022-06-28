/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:18 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:27:16 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	open_redirection(char *file_name, int check)
{
	int	fd;
	int	file_check;

	if (check == 1)
	{
		file_check = open (file_name, O_RDONLY);
		if (file_check != -1)
		{
			close (file_check);
			unlink (file_name);
		}
		fd = open (file_name, O_WRONLY | O_CREAT, 0644);
		return (fd);
	}
	else
	{
		file_check = open (file_name, O_WRONLY | O_APPEND);
		if (file_check != -1)
			fd = file_check;
		else
			fd = open (file_name, O_WRONLY | O_CREAT, 0644);
		return (fd);
	}
}

int	check_heredoc(char *name)
{
	int		fd[2];
	char	*temp;

	pipe (fd);
	temp = readline (">");
	while (ft_strncmp (name, temp, ft_strlen(temp)) != 0 || \
			ft_strncmp (name, temp, ft_strlen(name) != 0))
	{
		write (fd[1], temp, ft_strlen(temp));
		write (fd[1], "\n", 1);
		free (temp);
		temp = readline (">");
	}
	free (temp);
	close (fd[1]);
	return (fd[0]);
}

int	open_file(char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		g_status = errno - 1;
	}
	return (fd);
}

void	set_redirection(t_root *top, int fd, int in_or_out, int *check)
{
	if (fd < 0)
	{
		*check = 1;
		return ;
	}
	if (in_or_out == 0)
	{
		if (top->in_fd != 0)
			close (top->in_fd);
		top->in_fd = fd;
	}
	else
	{
		if (top->out_fd != 1)
			close (top->out_fd);
		top->out_fd = fd;
	}
}

int	do_redirection(t_root *top)
{
	t_node	*temp;
	int		check;

	check = 0;
	temp = top->left->left;
	while (temp != NULL)
	{
		if (ft_strncmp (temp->cmd, ">>", 2) == 0)
			set_redirection(top, open_redirection(temp->arg, 2), 1, &check);
		else if (ft_strncmp (temp->cmd, "<<", 2) == 0)
			set_redirection(top, check_heredoc (temp->arg), 0, &check);
		else if (ft_strncmp (temp->cmd, ">", 1) == 0)
			set_redirection(top, open_redirection(temp->arg, 1), 1, &check);
		else
			set_redirection(top, open_file (temp->arg), 0, &check);
		if (check != 0)
			return (1);
		temp = temp->left;
	}
	return (0);
}
