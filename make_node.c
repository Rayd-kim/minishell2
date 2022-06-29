/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 23:29:57 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_cmd(char *cut, t_node *start, t_list *env)
{
	t_node	*cmd;
	char	*str;

	cmd = (t_node *)malloc(sizeof(t_node));
	if (cmd == 0)
		exit (1);
	ft_memset (cmd, 0, sizeof(t_node));
	str = change_quote(cut, env);
	cmd->cmd = ft_strdup(str);
	start->right = cmd;
	if (str != cut)
		free(str);
}

void	make_arg(char *cut, t_node *start, t_list *env, t_root *root)
{
	char	*temp_free;
	char	*str;

	str = change_quote(cut, env);
	if (start->right->arg == NULL)
		start->right->arg = ft_strdup(str);
	else
	{
		temp_free = start->right->arg;
		start->right->arg = ft_strjoin (start->right->arg, root->bond);
		free (temp_free);
		temp_free = start->right->arg;
		start->right->arg = ft_strjoin (start->right->arg, str);
		free (temp_free);
	}
	if (str != cut)
		free(str);
}

void	make_node(char *split, t_root *start, t_list *env)
{
	char	**cut;
	int		cmd;
	int		i;

	cmd = 0;
	cut = ft_split(split, (char)255);
	i = 0;
	while (cut[i] != NULL)
	{
		if (check_redirection(cut[i]) != 0)
			make_redirection (cut[i], start, cut, &i);
		else if (cmd == 0)
		{
			make_cmd(cut[i], start->left, env);
			cmd++;
		}
		else
			make_arg(cut[i], start->left, env, start);
		i++;
	}
	split_free (cut);
}

t_root	*make_root(int root_in, int root_out, t_list *env)
{
	t_root	*ret;

	ret = (t_root *)malloc(sizeof(t_root));
	if (ret == 0)
		exit (1);
	ft_memset (ret, 0, sizeof(t_root));
	ret->in_fd = root_in;
	ret->out_fd = root_out;
	ret->bond[0] = (char)255;
	ret->env = env;
	return (ret);
}

t_root	*make_cmd_node(t_root *start, t_list *env)
{
	t_root	*temp;
	t_node	*cmd;
	t_root	*pipe;

	temp = start;
	if (temp->left != NULL)
	{
		pipe = make_root (0, 1, env);
		while (temp->right != NULL)
			temp = temp->right;
		temp->right = pipe;
		temp = temp->right;
	}
	cmd = (t_node *)malloc(sizeof(t_node));
	if (cmd == 0)
		exit (1);
	ft_memset (cmd, 0, sizeof(t_node));
	temp->left = cmd;
	return (temp);
}
