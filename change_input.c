/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:49:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 19:08:49 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_space(char *s)
{
	int	double_q;
	int	single_q;
	int	i;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			double_q++;
		else if (s[i] == '\'')
			single_q++;
		else if (s[i] == ' ' && double_q % 2 == 0 && single_q % 2 == 0)
			s[i] = (char)255;
		i++;
	}
}

void	change_pipe(char *s)
{
	int	double_q;
	int	single_q;
	int	i;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			double_q++;
		else if (s[i] == '\'')
			single_q++;
		else if (s[i] == '|' && double_q % 2 == 0 && single_q % 2 == 0)
			s[i] = (char)254;
		i++;
	}
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

char	*change_quote(char *str, t_list *env)
{
	int		i;
	char	*temp;
	char	*free_temp;
	char	*ret;

	free_temp = NULL;
	temp = check_env(str, env);
	if (temp != str)
	{
		while (1)
		{
			free_temp = temp;
			temp = check_env(temp, env);
			if (free_temp == temp)
				break ;
			free(free_temp);
		}
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			ret = remove_quote(temp, 2);
			if (ret != temp && free_temp != NULL)
				free (free_temp);
			return (ret);
		}
		else if (str[i] == '\'')
			return (remove_quote(temp, 1));
		i++;
	}
	return (temp);
}
