#include "minishell.h"

char	*check_home(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp("HOME=", temp->str, 5) == 0)
			return (ft_strchr(temp->str, '='));
		temp = temp->next
	}
	return (NULL);
}

int	main(char **arg, t_list *env)
{
	char	*home;

	if (arg[1] == NULL)
	{
		home = check_home(env);
		if (chdir(home + 1))
			printf("%s\n", strerror(errno));
		printf("%s\n", getcwd(NULL, 0));
		return (0);
	}

	if(chdir(arg[1]))
		printf("%s\n", strerror(errno));
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}
