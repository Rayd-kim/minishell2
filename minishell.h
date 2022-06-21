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

typedef struct s_node {
	char	*cmd;
	char	*arg;
	int		type;
	struct s_node	*left;
	struct s_node *right;
}		t_node;

typedef struct s_root {
	int	in_fd;
	int	out_fd;
	struct s_node	*left;
	struct s_root	*right;
}		t_root;

typedef struct s_list {
	char	*str;
	struct s_list	*prev;
	struct s_list	*next;
}		t_list;

void	change_input (char *s);
void	make_redirection (char *str, t_node	*start, char **cut, int *index);
int		check_redirection (char *str);
void	make_node(char *split, t_root *start);
t_list	*make_env(char **envp);
t_root	*make_cmd_node(t_root *start);
t_root	*make_root(int root_in, int root_out);
#endif