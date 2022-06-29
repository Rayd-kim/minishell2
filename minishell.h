/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:03:59 by youskim           #+#    #+#             */
/*   Updated: 2022/06/27 21:58:53 by youskim          ###   ########.fr       */
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
# include <signal.h>
# include "libft/libft.h"

# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

extern int g_status;

typedef struct s_node {
	char			*cmd;
	char			*arg;
	struct s_node	*left;
	struct s_node	*right;
}		t_node;

typedef struct s_list {
	char			*str;
	struct s_list	*next;
}		t_list;

typedef struct s_root {
	int				in_fd;
	int				out_fd;
	char			bond[2];
	char			**shell_envp;
	pid_t			pid;
	struct s_list	*env;
	struct s_node	*left;
	struct s_root	*right;
}		t_root;

t_list	*make_env(char **envp);
t_root	*make_cmd_node(t_root *start, t_list *env);
t_root	*make_root(int root_in, int root_out, t_list *env);
void	change_space(char *s);
void	change_pipe(char *s);
void	make_redirection(char *str, t_root	*root, char **cut, int *index);
int		check_redirection(char *str);
void	make_node(char *split, t_root *start, t_list *env);
void	exe_cmd(t_root *start, t_list *env);
int		do_redirection(t_root *top);
char	*change_quote(char *str, t_list *env);
char	*check_env_vari(char *str, t_list *env);
void	error_stdin(char *str, int check);
void	split_free(char **split);

int		check_whitespace(char *str);
int		check_pipe_close(char *str);
void	set_process_fd(t_root *top, int *fd);
int		check_redirection_close(char *str, char **split, char *temp);
int		check_quote(char *str, char **split, char *temp);
int		access_check(char *path);
int		pipe_check(t_root *top);
int		check_slash(char *str);
char	**make_command(t_node *node, t_root *top);

void	echo_process(t_root *top);
void	pwd_process(t_root *top);
void	env_process(t_root *top, t_list *env);
void	unset_process(t_root *top, t_list *env);
void	do_execve(char *path, t_root *top);
void	do_execve_null(t_root *top);

void	set_signal(void);
void	signal_end(int sig);
#endif
