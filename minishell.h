/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:59 by youskim           #+#    #+#             */
/*   Updated: 2022/06/24 18:04:00 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

# define REDI 1
# define CMD 2
# define ARG 3
# define PIPE 4

typedef struct s_node {
	char			*cmd;
	char			*arg;
	int				type;
	struct s_node	*left;
	struct s_node	*right;
}		t_node;

typedef struct s_root {
	int				in_fd;
	int				out_fd;
	struct s_node	*left;
	struct s_root	*right;
}		t_root;

typedef struct s_list {
	char			*str;
	struct s_list	*next;
}		t_list;

t_list	*make_env(char **envp);
t_root	*make_cmd_node(t_root *start);
t_root	*make_root(int root_in, int root_out);
void	change_input (char *s);
void	make_redirection (char *str, t_node	*start, char **cut, int *index);
int		check_redirection (char *str);
void	make_node(char *split, t_root *start, t_list *env);
void	exe_cmd(t_root *start, t_list *env);
void	do_redirection(t_root *top);
char	*change_quote(char *str, t_list *env);
char	*check_env_vari(char *str, t_list *env);
void	error_stdin(char *str);
void	split_free(char **split);
#endif
