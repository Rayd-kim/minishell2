#include "minishell.h"

t_list	*make_list(void)
{
	t_list	*ret;
	
	ret = (t_list *)malloc(sizeof(t_list));
	if (ret == 0)
		exit (1);
	ft_memset (ret, 0, sizeof(t_list));
	return (ret);
}

t_list	*make_env(char **envp)
{
	t_list	*ret;
	t_list	*temp;
	int		i;

	ret = make_list ();
	ret->str = envp[0];
	temp = ret;
	i = 0;
	while (envp[++i] != NULL)
	{
		temp->next = make_list ();
		temp->next->str = envp[i];
		temp = temp->next;
	}
	return (ret);
}
