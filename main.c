/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:46 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:07:35 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	free_left(t_node *top)
{
	t_node	*node;
	t_node	*free_node;

	node = top;
	if (node->right != NULL)
	{
		free (node->right->cmd);
		free (node->right->arg);
		free (node->right);
	}
	free_node = node;
	node = node->left;
	free (free_node);
	while (node != NULL)
	{
		free (node->cmd);
		free (node->arg);
		free_node = node;
		node = node->left;
		free (free_node);
	}
}

void	reset_root(t_root *start)
{
	t_root	*root;
	t_root	*free_root;

	root = start;
	while (root != NULL)
	{
		if (root->left != NULL)
			free_left (root->left);
		if (root->in_fd != 0)
			close (root->in_fd);
		if (root->out_fd != 1)
			close (root->out_fd);
		free_root = root;
		root = root->right;
		free (free_root);
	}
}

int	show_prompt(t_root *start, t_list *env)
{
	char	*temp;
	char	**split;
	int		i;

	temp = readline("minishell >>");
	add_history (temp);
	if (check_pipe_close(temp) != 0)
		return (1);
	change_pipe (temp);
	split = ft_split (temp, (char)254);
	if (split == NULL)
		exit (1);
	i = -1;
	while (split[++i] != NULL)
	{
		if (check_quote(split[i], split, temp) != 0)
			return (1);
		change_space(split[i]);
		make_node(split[i], make_cmd_node(start), env);
	}
	split_free (split);
	free (temp);
	return (0);
}

void	pid_check(t_root *start)
{
	int		now_pid;
	int		check;
	t_root	*temp;

	now_pid = 0;
	temp = start;
	while (temp->right != NULL)
		temp = temp->right;
	while (1)
	{
		now_pid = waitpid(0, &check, 0);
		if (now_pid == -1)
			break ;
		if (now_pid == temp->pid)
			g_status = check >> 8;
	}
}

void	sig_control_c(int sig)
{
	
}

int	main(int arg, char *argv[], char **envp)
{
	t_root	*start;
	t_list	*env;

	if (arg > 1 || ft_strncmp (argv[0], "./minishell", ft_strlen(argv[0])) != 0)
		exit (1);
	env = make_env (envp);
	signal(SIGINT, sig_control_c);
	while (1)
	{
		start = make_root (0, 1);
		if (show_prompt (start, env) == 0)
		{
			exe_cmd (start, env);
			pid_check(start);
		}
		reset_root(start);
	}
	return (0);
}
