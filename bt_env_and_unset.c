/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env_and_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:54:11 by youskim           #+#    #+#             */
/*   Updated: 2022/07/01 16:54:12 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (1)
	{
		if (temp != NULL)
			printf("%s\n", temp->str);
		else
			break ;
		temp = temp->next;
	}
}

void	env_process(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		prt_env(env);
		exit(0);
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	delete_env(t_list *env_list, char *args)
{
	t_list	*list;
	t_list	*prev;
	char	*temp;

	temp = ft_strjoin(args, "=");
	list = env_list;
	prev = NULL;
	while (list != NULL)
	{
		if (!ft_strncmp(temp, list->str, ft_strlen(temp)))
		{
			if (prev != NULL)
				prev->next = list->next;
			free(list->str);
			free (list);
			break ;
		}
		else
		{
			prev = list;
			list = list->next;
		}
	}
	free(temp);
}

void	bt_unset(char *args, t_list *env_list)
{
	int	i;

	i = 0;
	if (args[i] == '\0')
		return ;
	while (args[i] != '\0')
	{
		if (!ft_isalpha(*args))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(args, STDERR_FILENO);
			ft_putendl_fd("':  not a valid identifier", STDERR_FILENO);
			g_vari.status = 1;
			return ;
		}
		else
		{
			delete_env(env_list, args);
			g_vari.status = 0;
			return ;
		}
		i++;
	}
}

void	unset_process(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	if (top->left->right->arg != NULL)
		bt_unset(top->left->right->arg, env);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}
