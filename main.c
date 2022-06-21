#include "minishell.h"

t_root	*make_root (int	root_in, int root_out)
{
	t_root	*ret;

	ret = (t_root *)malloc(sizeof(t_root));
	if (ret == 0)
		exit (1);
	ft_memset (ret, 0, sizeof(t_root));
	ret->in_fd = root_in;
	ret->out_fd = root_out;
	return (ret);
}

t_root	*make_cmd_node(t_root *start)
{
	t_root	*temp;
	t_node	*cmd;
	t_root	*pipe;

	temp = start;
	if (temp->left != NULL)
	{
		pipe = make_root (0, 1);
		while (temp->right != NULL)
			temp = temp->right;
		temp->right = pipe;
		temp = pipe;
	}
	cmd = (t_node *)malloc(sizeof(t_node));
	if (cmd == 0)
		exit (1);
	ft_memset (cmd, 0, sizeof(t_node));
	temp->left = cmd;
	return (temp);
}

void	reset_root (t_root *start)
{
	//일단은 파이프 없을때만. 파이프 있으면 root도 오른쪽으로 돌면서 free해야함.
	t_node	*node;
	t_root	*root;
	t_node	*free_node;

	node = start->left;
	root = start;
	free (node->right->cmd);
	free (node->right->arg);
	free (node->right);
	free_node = node;
	node = node->left;
	while (node != NULL)
	{
		free (node->cmd);
		free (node->arg);
		free_node = node;
		node = node->left;
	}
	free (free_node);
	start->left = NULL;
}


int main(void)
{
	char	*temp;
	char	**split;
	t_root	*start;

	start = make_root (0, 1);
	while (1)
	{
	temp = readline("minishell >>");
	split = ft_split (temp, '|');
	if (split == NULL)
		exit (1);
	for (int i = 0; split[i] != NULL; i++)
	{
		change_input(split[i]);
		make_node(split[i], make_cmd_node(start));
	}
	reset_root (start);
	free (temp);
	//split도 free해야함.
	}
	return (0);
}


/*
int main(void)
{
	char	*temp;
	char	**split;
	t_root	*start;
	t_node	*node;

	start = make_root (0, 1);
	while (1)
	{
	temp = readline("minishell >>");
	if (temp == NULL)
		exit (1);
	split = ft_split (temp, '|');
	if (split == NULL)
		exit (1);
	for (int i = 0; split[i] != NULL; i++)
	{
		change_input(split[i]);
		make_node(split[i], make_cmd_node(start));
	}
	node = start->left;
	while (node->left != NULL)
	{
		printf ("\nredirection cmd :%s arg : %s\n", node->left->cmd, node->left->arg);
		node = node->left;
	}
	printf ("\ncommand cmd : %s arg %s\n", start->left->right->cmd, start->left->right->arg);
	reset_root (start);
	free (temp);
	}
	return (0);
}
*/