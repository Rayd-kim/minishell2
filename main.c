#include "minishell.h"
/*
int main(void)
{
	char	*temp;
	char	**split;
	t_node	*start;

	start = (t_node *)malloc(sizeof(t_node));
	if (start == 0)
		exit (1);
	ft_memset (start, 0, sizeof(t_node));
	while (1)
	{
	temp = readline("minishell >>");
	split = ft_split (temp, '|');
	for (int i = 0; split[i] != NULL; i++)
	{
		change_input(split[i]);
		make_node(split[i], start);
	}
	free (temp);
	}
	return (0);
}
*/

int main(void)
{
	char	*temp;
	char	**split;
	t_node	*start;
	t_node	*node;

	start = (t_node *)malloc(sizeof(t_node));
	ft_memset (start, 0, sizeof(t_node));
	while (1)
	{
	temp = readline("minishell >>");
	split = ft_split (temp, '|');
	for (int i = 0; split[i] != NULL; i++)
	{
		change_input(split[i]);
		make_node(split[i], start);
	}
	node = start;
	while (node->left != NULL)
	{
		printf ("redirection cmd :%s arg : %s\n", node->left->cmd, node->left->arg);
		node = node->left;
	}
	if (start->right != NULL)
		printf ("command cmd : %s arg %s\n", start->right->cmd, start->right->arg);
	free (temp);
	}
	return (0);
}
