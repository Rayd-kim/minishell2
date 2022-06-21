#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft/libft.h"

typedef struct node {
	char	*cmd;
	char	*arg;
	int		type;
	struct node	*left;
	struct node *right;
}		t_node;

void	change_input (char *s);

// void	make_node (char **split)
// {
// 	t_node	*start;

// 	start = (t_node *)malloc(sizeof(t_node));
// 	if (start == 0)
// 		return ;
// 	int	i = 0;
// 	while (split[i] != NULL)
// 	{
// 		if (split[i] == redirection)


// 		else if (split)
// 	}
// }


int main(void)
{
	char	*temp;
	char	**split;

	while (1)
	{
	temp = readline("minishell >>");
	change_input (temp);
	split = ft_split (temp, (char)255);
	if (split == NULL)
	{
		printf("ERROR\n");
		return (1);
	}
	for (int i = 0; split[i] != NULL; i++)
		printf ("%d번째 %s\n",i, split[i]);
	



	int i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free (split[i]);
	free (split);
	free (temp);
	}
	return (0);
}
