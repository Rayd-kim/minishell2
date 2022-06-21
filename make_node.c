#include "minishell.h"

void	make_cmd(char *str, t_node *start)
{
	t_node	*cmd;

	cmd = (t_node *)malloc(sizeof(t_node));
	if (cmd == 0)
		exit (1);
	ft_memset (cmd, 0, sizeof(t_node));
	cmd->type = CMD;
	cmd->cmd = ft_strdup(str);
	start->right = cmd;
}

void	make_arg(char *str, t_node *start)
{
	char	*temp_free;

	if (start->right->arg == NULL)
		start->right->arg = ft_strdup(str);
	else
	{
		temp_free = start->right->arg;
		start->right->arg = ft_strjoin (start->right->arg, " ");
		free (temp_free);
		temp_free = start->right->arg;
		start->right->arg = ft_strjoin (start->right->arg, str);
		free (temp_free);
	}
}

void	make_node(char *split, t_node *start)
{
	char	**cut;
	int		cmd = 0;
	int		i;

	cut = ft_split(split, (char)255);
	i = 0;
	while (cut[i] != NULL)
	{
		if (check_redirection(cut[i]) != 0)
			make_redirection (cut[i], start, cut, &i);
		else if (cmd == 0)
		{
			make_cmd(cut[i], start);
			cmd++;
		}
		else
			make_arg(cut[i], start);
		i++;
	}
	i = -1;
	while (cut[++i] != NULL)
		free (cut[i]);
	free (cut[i]);
	free (cut);
}