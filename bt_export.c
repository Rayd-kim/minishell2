#include "minishell.h"

int find_index(char* str)
{
    int i;
    int flag;

    flag = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            flag = 1;
            break;
        }
        i++;
    }
    if (flag == 0)
        return 0;
    else
        return i;    
}

char* custom_strjoin(char* str1, char* str2)
{
	int i;
	int j;
	int a;
	int b; 

	i = 0;
	j = 0;
	a = ft_strlen(str1);
	b = ft_strlen(str2);
	char* arr = malloc(sizeof(char) * (a + b + 1));
	while (str1[i])
	{
        arr[i] = str1[i];
        i++;
    }	
	while (str2[j])
    {
        arr[i] = str2[j];
        i++;
        j++;
    }
	arr[i] = '\0';
    free(str1);
    free(str2);
	return arr;
}

char* custom_split(char* str, int idx)
{
    int i;
    int j;
    int len;

    len = ft_strlen(str);
    char* arr1 = malloc(sizeof(char) * (idx + 2));
    char* arr2 = malloc(sizeof(char) * (len - idx));
    i = 0;
    j = 0;
    while (i < idx)
    {
        arr1[i] = str[i];
        i++;
    }
    arr1[i] = '\"';
    if (len - idx == 0)
    {
        arr1[i + 1] = '\"';
        arr1[i + 2] = '\0'; 
        return arr1;
    }
    arr1[i + 1] = '\0';
    while (str[i])
        arr2[j++] = str[i++];
    arr2[j] = '\"';
    arr2[j + 1] = '\0';
    return (custom_strjoin(arr1, arr2));
}

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
	idx = (ptr - args);
	while (tmp->next && ptr)
	{
		i = 0;
		while (args[i] == tmp->str[i])
		{
			if (i == idx)
			{
				free(tmp->str);
				tmp->str = ft_strdup(args);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	if (ptr != NULL)
	{
		tmp->next = make_list();
		tmp->next->str = ft_strdup(args);
	}
	return (EXIT_SUCCESS);
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
	int equal;

	i = 0;
	flag = 1;
	equal = 1;	
	flag = check_valid(args, i, flag);
	if (flag)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

void	null_args(t_list *env_list)
{
	char	*str;
	int		i;

	while (env_list)
	{
		i = find_index(env_list->str);
		str = custom_split(env_list->str, i + 1);
		printf("declare -x %s\n", str);
		free(str);
		env_list = env_list->next;
	}
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
		if (check_dup(args[i++], env_list))
			return (EXIT_FAILURE);
	}
	return (0);
}

void	export_process_no_arg(t_root *top, t_list *env)
{
	int		fd[2];
	char	**command;
	int		ret;

	pipe(fd);
	top->pid = fork();
	if (top->pid == 0)
	{
		set_process_fd(top, fd);
		command = make_command(top->left, top);
		ret = bt_export(command, env);
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