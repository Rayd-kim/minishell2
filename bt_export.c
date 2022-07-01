#include "minishell.h"

void prt_export_msg(char *args)
{
    ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	check_dup(char *args, t_list *env_list)
{
	char	*ptr;
	int		idx;
	int		i;
	t_list *tmp;

	tmp = env_list;
	ptr = ft_strchr(args, '=');
	if (ptr == NULL)
		return (0);
	idx = (ptr - args);
	while (tmp && ptr)
	{
		i = 0;
		while (args[i] == tmp->str[i])
		{
			if (i == idx)
			{
				free(tmp->str);
				tmp->str = ft_strdup(args);
				return (0);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_valid(char *args, int i, int flag)
{
	while (args[i])
	{
		if (ft_isalpha(args[0]) && args[i] != '\0')
		{
			if ((args[i] >= 48 && args[i] <= 57) || ft_isalpha(args[i]))
				flag = 0;
			else if (args[i] == '=')
			{
				if (args[i + 1] == '\0' || i == 0)
				{
					i++;
					flag = 0;
					continue ;
				}
			}
		}
		if (flag)
		{
			prt_export_msg(args);
			break ;
		}
		i++;
	}
	return (flag);
}

int	check_alpha(char *args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	flag = check_valid(args, i, flag);
	if (flag)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

void	null_args(t_list *env_list)
{
	int		i;

	while (env_list)
	{
		i = 0;
		printf("declare -x ");
		while (env_list->str[i])
		{
			printf("%c", env_list->str[i]);
			if (env_list->str[i] == '=')
				break;
			i++;			
		}
		i++;
		printf("%c", '\"');
		while (env_list->str[i])
			printf("%c", env_list->str[i++]);
		printf("%c\n", '\"');
		env_list = env_list->next;
	}
}

void	add_env(char *args, t_list *env_list)
{
	t_list	*temp;

	temp = env_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = make_list();
	temp->next->str = ft_strdup(args);
}

int	bt_export(char **args, t_list *env_list)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		null_args(env_list);
		return (EXIT_SUCCESS);
	}
	while (args[i] != NULL)
	{
		if (check_alpha(args[i++]))
			return (1);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (check_dup(args[i], env_list))
			add_env(args[i], env_list);
		i++;
	}
	return (0);
}

void	export_process_no_arg(t_root *top, t_list *env)
{
	int		fd[2];
	char	**command;

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		command = make_command(top->left, top);
		bt_export(command, env);
		split_free (command);
		exit(0);
	}
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	export_process_arg(t_root *top, t_list *env)
{
	int		fd[2];
	char	**command;

	pipe(fd);
	command = make_command(top->left, top);
	g_vari.status = bt_export(command, env);
	split_free (command);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}

void	export_process(t_root *top, t_list *env)
{
	if (top->left->right->arg == NULL)
		export_process_no_arg(top, env);
	else
		export_process_arg(top, env);
}