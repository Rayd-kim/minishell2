#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include "libft/libft.h"

# define REDI 1
# define CMD 2
# define ARG 3
# define PIPE 4

typedef struct node {
	char	*cmd;
	char	*arg;
	int		type;
	struct node	*left;
	struct node *right;
}		t_node;

typedef struct root {
	int	in_fd;
	int	out_fd;
	struct node	*left;
	struct root *right;
}		t_root;

void	change_input (char *s);
void	make_redirection (char *str, t_node	*start, char **cut, int *index);
int		check_redirection (char *str);
void	make_node(char *split, t_root *start);

#endif