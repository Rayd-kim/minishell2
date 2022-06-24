/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:49:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:04:08 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

int		cut_num (char *s)
{
	int	check = 1;
	int	quote = 0;
	int	len = 0;

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\"')
			quote++;
		else if (!(s[i] == ' ' && quote % 2 == 0))
			check = 0;
		else if (s[i] == ' ' && quote % 2 == 0 && check == 0)
		{
			len++;
			check = 1;
		}
	}
	return (len);
}

int	check_space (char *s, int i)
{
	int	check;
	int	quote;

	check = 1;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			quote++;
		else if (!(s[i] == ' ' && quote % 2 == 0))
			check = 0;
		else if (s[i] == ' ' && quote % 2 == 0 && check == 0)
			return (i);
		i++;
	}
	return (i);
}

char	*in_split (char *s, int start, int end)
{
	char	*ret;
	int		i;
	int		len;

	len = end - start;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

char **cut_str (char *s, int num)
{
	int	i;
	int	k;
	int	temp;
	char	**split;

	split = (char **)malloc(sizeof(char) * (num + 1));
	if (split == 0)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		temp = check_space (s, i);
		split[k] = in_split (s, i , temp);
		printf ("%s\n", split[k]);
		k++;
		if (s[temp] == '\0')
			break;
		i = temp + 1;
	}
	printf ("%d\n", k);
	split[k] = NULL;
	return (split);
}

char	**minishell_split (char *s)
{
	int	num;
	char	**split;

	if (s == NULL)
		return (NULL);
	num = cut_num(s) + 1;
	split = (char **)malloc(sizeof(char) * (num + 1));
	if (split == 0)
		return (NULL);
	split = cut_str (s, num);
	for (int i = 0; split[i] != NULL; i++)
		printf ("%d번째 %s\n",i, split[i]);
	return (split);
}
