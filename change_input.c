/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:49:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:03:17 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_input(char *s)
{
	int	double_q = 0;
	int	single_q = 0;

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\"')
			double_q++;
		else if (s[i] == '\'')
			single_q++;
		else if (s[i] == ' ' && double_q % 2 == 0 && single_q % 2 == 0)
			s[i] = (char)255;
	}
}

int	env_len(char *path)
{
	int	i;

	i = 0;
	while (path[i] != ' ' && path[i] != '\"' && path[i] != '\0' && path[i] != '\'')
		i++;
	return (i);
}

char	*set_env_vari(char *str, t_list *env, char *path) //path은 $PATH같은 환경변수에서 $바로 뒤의 주소값
{
	char	*free_temp;
	char	*join;
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '$')
		i++;
	temp = ft_substr(str, 0, i);
	join = ft_strjoin(temp, (env->str + env_len(path) + 1));
	free(temp);
	free_temp = join;
	i += env_len(path) + 1;
	temp = ft_substr(str, i, ft_strlen(&str[i]));
	join = ft_strjoin(join, temp);
	free(free_temp);
	free(temp);
	return (join);
}

char	*set_env_empty(char *str, char *path)
{
	char	*free_temp;
	char	*join;
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '$')
		i++;
	temp = ft_substr(str, 0, i);
	i += env_len(path) + 1;
	free_temp = ft_substr(str, i, ft_strlen(&str[i]));
	join = ft_strjoin(temp, free_temp);
	free(free_temp);
	free(temp);
	return (join);
}

int	path_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char	*check_env_vari(char *str, t_list *env)
{
	t_list	*temp;
	char	*path;

	path = ft_strchr(str, '$');
	temp = env;
	if (path != NULL)
	{
		path = path + 1;
		while (temp != NULL)
		{
			if (ft_strncmp(path, temp->str, path_len(temp->str)) == 0)
				return (set_env_vari(str, temp, path));
				// return (check_env_vari(set_env_vari(str, temp, path), env));
			temp = temp->next;
		}
		return (set_env_empty(str, path));
	}
	return (str);
}

char	*remove_quote(char *str, int type)
{
	char	*ret;
	int		i;
	int		k;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (ret == 0)
		exit (1);
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (type == 1 && str[i] != '\'')
		{
			ret[k] = str[i];
			k++;
		}
		else if (type == 2 && str[i] != '\"')
		{
			ret[k] = str[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (ret);
}

char	*check_env(char *str, t_list *env)
{
	int		quote_single;
	int		i;

	i = 0;
	quote_single = 0;
	while(str[i])
	{
		if (str[i] == '\'')
			quote_single++;
		else if (str[i] == '$' && quote_single % 2 == 0)		
			return (check_env_vari(str, env));
		i++;
	}
	return (str);
}

char	*change_quote(char *str, t_list *env)
{
	int		i;
	char	*temp;
	char	*free_temp;
	char	*ret;

	temp = check_env(str, env);
	if (temp != str)
	{
		while (1)
		{
			free_temp = temp;
			temp = check_env(temp, env);
			if (free_temp == temp)
			{
				// free(free_temp);
				break ;
			}
			free(free_temp);
		}
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			ret = remove_quote(temp, 2);
			// free (free_temp);
			return (ret);
		}
			// return (remove_quote(temp, 2));
		else if (str[i] == '\'')
			return (remove_quote(temp, 1));
		i++;
	}
	return (temp);
}



// char	*change_quote(char *str, t_list *env)
// {
// 	int		i;
// 	char	*temp;
// 	char	*ret;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"')
// 		{
// 			temp = check_env_vari(str, env);
// 			if (temp != str)
// 			{
// 				ret = remove_quote(temp, 2);
// 				free(temp);
// 				return (ret);
// 			}
// 			else
// 				return (remove_quote(temp, 2));
// 		}
// 		else if (str[i] == '\'')
// 			return (remove_quote(str, 1));
// 		else if (str[i] == '$')
// 			return (check_env_vari(str, env));
// 		i++;
// 	}
// 	return (str);
// }
