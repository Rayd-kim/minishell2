#include "minishell.h"

char	*check_home(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp("HOME=", temp->str, 5) == 0)
			return (ft_strchr(temp->str, '='));
		temp = temp->next;
	}
	return (NULL);
}

void set_pwd(t_list* env, char* oldpwd, char* pwd)
{
    while (env)
    {
		if (ft_strncmp("OLDPWD=", env->str, 7))
		{
			free(env->str);
			env->str = ft_strjoin("OLDPWD=", oldpwd);
		}
		if (ft_strncmp("PWD=", env->str, 4))
		{
			free(env->str);
			env->str = ft_strjoin("PWD=", pwd);
		}
		env = env->next;
    }
}

void	bt_cd(char **arg, t_list *env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (arg[1] == NULL || !ft_strncmp(arg[1], "~", 2))
	{
		home = check_home(env);
		if (chdir(home + 1))
		{
			printf("%s\n", strerror(errno));
			g_vari.status = errno - 1;
		}
	}
	else if(chdir(arg[1]))
	{
		printf("%s\n", strerror(errno));
		g_vari.status = errno - 1;
	}
	pwd = getcwd(NULL, 0);
	set_pwd(env, oldpwd, pwd);
}

void	cd_process(t_root *top)
{
	int		fd[2];
	char	**command;

	pipe(fd);
	command = make_command(top->left, top);
	bt_cd(command, top->env);
	split_free (command);
	if (pipe_check(top) == 0)
		top->right->in_fd = fd[0];
	else
		close (fd[0]);
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
	// if (top->in_fd == 0 && top->right == NULL) // 이때만 실행 될수있게
}
