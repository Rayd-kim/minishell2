#include "minishell.h"

int	pipe_check(t_root *top)
{
	if (top->right != NULL)
	{
		if (top->right->in_fd == 0)
			return (0);
	}
	return (1);
}

int	check_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	access_check(char *path)
{
	int	fd;

	fd = open (path, O_RDONLY);
	if (fd != -1)
		return (0);
	else
	{
		close (fd);
		return (1);
	}
}

char	**make_command(t_node *node, t_root *top)
{
	char	**command;
	char	*temp;
	char	*free_temp;

	temp = ft_strjoin(node->right->cmd, top->bond);
	free_temp = temp;
	temp = ft_strjoin(free_temp, node->right->arg);
	free(free_temp);
	command = ft_split(temp, (char)255);
	free(temp);
	return (command);
}
