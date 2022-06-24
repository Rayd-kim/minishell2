/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:04:11 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:04:18 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(char *name) //here_doc 구현하는 함수. readline으로 shell상에서 받아오면서 체크.
{
	int		fd[2];
	char	*temp;

	pipe (fd);
	temp = readline (">");
	while (ft_strncmp (name, temp, ft_strlen(temp)) != 0 || ft_strncmp (name, temp, ft_strlen(name) != 0))
	{
		write (fd[1], temp, ft_strlen(temp));
		write (fd[1], "\n", 1);
		free (temp);
		temp = readline (">");
	}
	free (temp);
	close (fd[1]);
	return (fd[0]);
	//우선 pipex에서 한거처럼 비슷하게 구현했는데, 아직 좀더 수정필요할듯.
}

int	main(void)
{
	int fd = check_heredoc ("hi");
	// getenv ("PATH");
	pid_t pid = fork ();

	if (pid == 0)
	{
		dup2 (fd, 0);
		printf ("%d\n", execve("/bin/cat", NULL, NULL));
	}
	printf ("end\n");
	return 0;
}
