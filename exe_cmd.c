/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:37 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:03:38 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_command(t_node *node)
{
	char	**command;
	char	*temp;
	char	*free_temp;

	temp = ft_strjoin(node->right->cmd, " ");
	free_temp = temp;
	temp = ft_strjoin(free_temp, node->right->arg);
	free(free_temp);
	command = ft_split(temp, ' ');
	free(temp);
	return (command);
}

void	do_execve(char *path, t_root *top)
{
	int		status;
	pid_t	pid;
	char	**command;

	pid = fork();
	if (pid == 0)
	{
		dup2(top->in_fd, 0);
		dup2(top->out_fd, 1);
		command = make_command(top->left);
		if (execve(path, command, NULL) == -1)
			error_stdin(path);
	}
	waitpid(pid, &status, 0);
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
	while (split[i] != NULL)
	{
		path = ft_strjoin (split[i], "/");
		temp = path;
		path = ft_strjoin (temp, top->left->right->cmd);
		free (temp);
		if (access(path, X_OK) == 0)
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

void	do_cmd(t_root *top, t_list *env) //외부함수 체크 빌트인은 외부함수 체크전에 확인해서 진행하기.
{
	t_list	*list;

	list = env;
	while (list != NULL)
	{
		if (ft_strncmp(list->str, "PATH=", 5) == 0)
			break;
		list = list->next;
	}
	if (list != NULL)
		check_cmd (list->str, top);
}

void	exe_cmd(t_root *start, t_list *env)
{
	t_root	*root_temp;
	t_list	*temp;

	temp = env;
	root_temp = start;
	while (root_temp != NULL)
	{
		if (root_temp->left != NULL)
		{
			do_redirection(root_temp);
		//이 밑으로는 아직 구현중.

			do_cmd(root_temp, env);
		}
			root_temp = root_temp->right;
		//fd값 조정해주기
		//root_temp의 fd_out을 root_temp->right의 fd_in으로 (오류날때는?)
	}
}
