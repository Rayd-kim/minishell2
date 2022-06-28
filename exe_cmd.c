/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:37 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:06:37 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	do_execve_null(t_root *top)
{
	int		fd[2];
	char	buffer[10];
	int		len;

	pipe (fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		len = read (top->in_fd, buffer, 10);
		while (len != 0)
		{
			write (top->out_fd, buffer, len);
			len = read (top->in_fd, buffer, 10);
		}
		close (fd[0]);
		close (fd[1]);
		if (top->in_fd != 0)
			close (top->in_fd);
		exit (0);
	}
	if (pipe_check(top) == 0)
	{
		top->right->in_fd = fd[0];
		if (top->in_fd != 0)
			close (top->in_fd);
		close (fd[1]);
	}
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	set_process_fd(t_root *top, int *fd)
{
	if (top->out_fd == 1 && pipe_check(top) == 0)
	{
		dup2(fd[1], 1);
		dup2(top->in_fd, 0);
		if (top->in_fd != 0)
			close (top->in_fd);
		close (fd[0]);
		top->right->in_fd = fd[0];
	}
	else
	{	
		dup2(top->in_fd, 0);
		if (top->in_fd != 0)
			close (top->in_fd);
		dup2(top->out_fd, 1);
	}
}

void	do_execve(char *path, t_root *top)
{
	char	**command;
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		command = make_command(top->left, top);
		if (execve(path, command, NULL) == -1)
			error_stdin (path, check_slash(top->left->right->cmd));
	}
	if (pipe_check(top) == 0)
	{
		top->right->in_fd = fd[0];
		if (top->in_fd != 0)
			close (top->in_fd);
		close (fd[1]);
	}
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	check_cmd(char *str, t_root *top)
{
	char	**split;
	char	*temp;
	char	*path;
	char	*copy;
	int		i;

	i = 0;
	copy = ft_strdup(ft_strchr(str, '/'));
	split = ft_split(copy, ':');
	free (copy);
	while (split[i] != NULL && check_slash(top->left->right->cmd) == 0)
	{
		path = ft_strjoin (split[i], "/");
		temp = path;
		path = ft_strjoin (temp, top->left->right->cmd);
		free (temp);
		if (access_check(path) == 0)
		{
			do_execve (path, top);
			split_free(split);
			free(path);
			return ;
		}
		free(path);
		i++;
	}
	split_free(split);
	do_execve (top->left->right->cmd, top);
}

int	check_builtin(char *str, t_root *top, t_list *env)
{
	if (ft_strncmp(str, "echo", ft_strlen (str)) == 0)
		echo_process(top);
	// else if (ft_strncmp(str, "cd", ft_strlen (str)) == 0)
	else if (ft_strncmp(str, "env", ft_strlen (str)) == 0)
		env_process(top, env);
	else if (ft_strncmp(str, "unset", ft_strlen (str)) == 0)
		unset_process(top, env);
	// else if (ft_strncmp(str, "export", ft_strlen (str)) == 0)
	else if (ft_strncmp(str, "pwd", ft_strlen (str)) == 0)
		pwd_process(top);
	// else if (ft_strncmp(str, "exit", ft_strlen (str)) == 0)
	else
		return (1);
	return (0);
}


void	do_cmd(t_root *top, t_list *env)
{
	t_list	*list;

	list = env;
	while (list != NULL && top->left->right != NULL)
	{
		if (check_builtin(top->left->right->cmd, top, env) == 0)
			return ;
		else if (ft_strncmp(list->str, "PATH=", 5) == 0)
		{
			check_cmd (list->str, top);
			return ;
		}
		list = list->next;
	}
	if (top->left->right == NULL)
		do_execve_null (top);
	else
		do_execve (top->left->right->cmd, top);
}

void	exe_cmd(t_root *start, t_list *env)
{
	t_root	*root_temp;
	int		fd[2];

	root_temp = start;
	while (root_temp != NULL)
	{
		if (root_temp->left != NULL)
		{
			if (do_redirection(root_temp) == 0)
				do_cmd(root_temp, env);
			else
			{
				if (root_temp->right != NULL && pipe_check(root_temp) == 0)
				{
					pipe(fd);
					close (fd[1]);
					root_temp->right->in_fd = fd[0];
					if (root_temp->in_fd != 0)
						close (root_temp->in_fd);
				}
			}
		}
			root_temp = root_temp->right;
	}
}
