/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:49:53 by youskim           #+#    #+#             */
/*   Updated: 2022/06/18 16:15:43 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>

void	change_input (char *s)
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
