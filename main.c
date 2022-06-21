#include "minishell.h"

void	free_left (t_node *top)
{
	t_node	*node;
	t_node	*free_node;

	node = top;
	free (node->right->cmd);
	free (node->right->arg);
	free (node->right);
	node = node->left;
	while (node != NULL)
	{
		free (node->cmd);
		free (node->arg);
		free_node = node;
		node = node->left;
		free (free_node);
	}
}

void	reset_root (t_root *start)
{
	t_root	*root;
	t_root	*free_root;

	root = start;
	while (root != NULL)
	{
		if (root->left != NULL)
			free_left (root->left);
		free_root = root;
		root = root->right;
		if (free_root != start)
			free (free_root);
	}
	start->left = NULL;
}

void	show_prompt (t_root *start)
{
	char	*temp;
	char	**split;
	int		i;

	temp = readline("minishell >>");
	split = ft_split (temp, '|');
	if (split == NULL)
		exit (1);
	i = -1;
	while (split[++i] != NULL)
	{
		change_input(split[i]);
		make_node(split[i], make_cmd_node(start));
		free (split[i]);
	}
	free (split);
	free (temp);
}

// void	exe_cmd(t_root *start)
// {
// 	t_node	*node_temp;
// 	t_root	*root_temp;

// 	root_temp = start;
// 	while (root_temp != NULL)
// 	{
// 		node_temp = root_temp->left;
// 		while (node_temp != NULL)
// 		{
// 			//do_redirection(node_temp);
// 			node_temp = node_temp->left;
// 		}
// 		//do_command(root->temp->left->right);
// 		root_temp = root_temp->right;
// 		//fd값 조정해주기
// 	}
// }

int main(int arg, char *argv[], char **envp)
{
	t_root	*start;
	t_list	*env;

	if (arg > 1 || ft_strncmp (argv[0], "./minishell", ft_strlen(argv[0])) != 0)
		exit (1);
	start = make_root (0, 1);
	env = make_env (envp);
	// t_list	*temp;
	// temp = env;
	// while (temp != NULL)
	// {
	// 	printf("%s\n", temp->str);
	// 	temp = temp->next;
	// }
	while (1)
	{
		// reset_root(start);
		show_prompt (start);
		t_root	*root;
		t_node	*node;
		
		root = start;
		while (root != NULL)
		{
			node = root->left;
			while (node != NULL)
			{
				printf ("\nredirection cmd %s arg %s\n", node->cmd, node->arg);
				if (node->right != NULL)
					printf ("command cmd %s arg %s\n", node->cmd, node->arg);
				node = node->left;
			}
			root = root->right;
		}
		//start를 인자로 넘겨서 순회하면서 redirection->명령어->pipe순으로 실행해야됨.
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