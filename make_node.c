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
	str = change_quote(cut, env);  //따옴표 제거하면서 $환경변수 확인
	cmd->cmd = ft_strdup(str);
	start->right = cmd;
	if (str != cut)
		free(str);
}

void	make_arg(char *cut, t_node *start, t_list *env, t_root *root)
{
	char	*temp_free;
	char	*str;

	str = change_quote(cut, env); //따옴표 제거하면서 $환경변수 확인
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
			make_redirection (cut[i], start->left, cut, &i);
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

t_root	*make_root(int root_in, int root_out) //root만드는 함수. 인자로 들어온 정수를 stdin, stdout 로 각각 저장.
{
	t_root	*ret;

	ret = (t_root *)malloc(sizeof(t_root));
	if (ret == 0)
		exit (1);
	ft_memset (ret, 0, sizeof(t_root));
	ret->in_fd = root_in;
	ret->out_fd = root_out;
	ret->bond[0] = (char)255;
	return (ret);
}

//파이프 수만큼 미리 노드들을 만들어 놓지않고, 반복문 돌때마다 노드를 탐색해서 필요한 만큼만 만드는 함수.
//반환값으로는 각 파이프라인의 명령어와 리다이렉션의 최상위 root를 반환한다.
t_root	*make_cmd_node(t_root *start) 
{
	t_root	*temp;
	t_node	*cmd;
	t_root	*pipe;

	temp = start;
	if (temp->left != NULL) //왼쪽이 NULL이 아니라는 뜻은, 현재 파이프로부터 넘어왔다는 뜻. 새로운 파이프라인의 명령어를 담을 root를 만들어준다.
	{
		pipe = make_root (0, 1);
		while (temp->right != NULL)
			temp = temp->right;
		temp->right = pipe;
		temp = temp->right; //temp가 현재 명령어라인의 최상의 root를 가르키도록.
	}
	cmd = (t_node *)malloc(sizeof(t_node));
	if (cmd == 0)
		exit (1);
	ft_memset (cmd, 0, sizeof(t_node));
	temp->left = cmd;
	return (temp);
}
