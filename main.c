#include "minishell.h"

void	free_left (t_node *top)
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
	start->right = NULL;
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
	i = 0;
	while (split[i] != NULL)
	{
		change_input(split[i]);
		make_node(split[i], make_cmd_node(start));
		free (split[i]);
		i++;
	}
	free (split);
	free (temp);
}

void	exe_cmd(t_root *start)
{
	t_node	*node_temp;
	t_root	*root_temp;

	root_temp = start;
	while (root_temp != NULL)
	{
		node_temp = root_temp->left;
		while (node_temp != NULL)
		{
			//do_redirection(node_temp);
			node_temp = node_temp->left;
		}
		//do_command(root->temp->left->right);
		root_temp = root_temp->right;
		//fd값 조정해주기
	}
}


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
		reset_root(start);
		show_prompt (start);
		//exe_cmd (start);

		// t_root	*root;
		// t_node	*node;
		
		// root = start;
		// while (root != NULL)
		// {
		// 	node = root->left;
		// 	while (node != NULL)
		// 	{
		// 		if (node->right != NULL)
		// 			printf ("\ncommand cmd %s arg %s\n", node->right->cmd, node->right->arg);
		// 		node = node->left;
		// 		if (node != NULL)
		// 			printf ("redirection cmd %s arg %s\n\n", node->cmd, node->arg);
		// 	}
		// 	root = root->right;
	}
		}
	return (0);
}