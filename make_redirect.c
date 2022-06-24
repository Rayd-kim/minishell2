/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:55 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:03:57 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strncmp (&str[i], ">>", 2) == 0)
			return (2);
		else if (ft_strncmp (&str[i], "<<", 2) == 0)
			return (2);
		else if (ft_strncmp (&str[i], ">", 1) == 0)
			return (1);
		else if (ft_strncmp (&str[i], "<", 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*cmd_redirection(char *str)
{
	char	*ret;
	int		len;
	int		i;
	int		k;

	len = check_redirection(str);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		exit (1);
	i = 0;
	k = 0;
	while (k < len)
	{
		if (str[i] == '>' || str[i] == '<')
		{
			ret[k] = str[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	free(str);
	return (ret);
}

char	*arg_redirection(char *str, char **cut, int *index)
{
	int	i;

	i = 0;
	while (str[i] != '>' && str[i] != '<')
		i++;
	if (str[i + 1] == '\0')
	{
		*index = *index + 1;
		return (ft_strdup(cut[*index]));
	}
	else if (str[i + 1] == '>' || str[i + 1] == '<')
	{
		if (str[i + 2] == '\0')
		{
			*index = *index + 1;
			return (ft_strdup(cut[*index]));
		}
		else
			return (ft_strdup(&str[i + 2]));
	}
	else
		return (ft_strdup(&str[i + 1]));
}

void	make_redirection(char *str, t_node	*start, char **cut, int *index)
{
	t_node	*temp;
	t_node	*redirect;

	redirect = (t_node *)malloc(sizeof(t_node));
	if (redirect == 0)
		exit(1);
	ft_memset (redirect, 0, sizeof(t_node));
	temp = start;
	while (temp->left != NULL)
		temp = temp->left;
	redirect->type = REDI;
	redirect->cmd = cmd_redirection (str);
	redirect->arg = arg_redirection (str, cut, index);
	temp->left = redirect;
}
