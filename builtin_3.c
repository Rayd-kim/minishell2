#include "minishell.h"

void	unset_process(t_root *top, t_list *env)
{
	int		fd[2];

	pipe(fd);
	bt_unset(top->left->right->arg, env);
	if (pipe_check(top) == 0)
	{
		top->right->in_fd = fd[0];
		if (top->in_fd != 0)
			close (top->in_fd);
		close (fd[1]);
	}
	if (top->in_fd != 0)
		close (top->in_fd);
	close (fd[1]);
}