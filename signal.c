#include "minishell.h"
#include <termios.h>


void	signal_handler(int sig)
{
	// struct termios	term;

	if (sig == CTRL_C)
	{
		g_status = 1;
		rl_on_new_line();
		rl_redisplay();
    	write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// tcgetattr(1, &term);
		// tcsetattr(1, TCSANOW, &term);
	}
}

// void	handle_signal(int signo)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = waitpid(-1, &status, WNOHANG);
// 	//-1 : 자식 프로세스를 기다림.
// 	//status : 자식 프로세스가 종료되면 자식 pid값이 할당 됨.
// 	//WNOHANG : 자식 프로세스가 종료되지 않아서 pid를 회수할 수 없는 경우 반환값으로 0을 받음.
// 	if (signo == SIGINT){
// 		if (pid == -1)
// 		//pid == -1 : 자식 프로세스가 없는 경우
// 		{
// 		rl_on_new_line();//개행을 실행하기 위한 엔터 역할
// 		rl_redisplay();// 입력받은 것 다시 출력
// 		ft_putstr_fd("  \n",1);//개행
// 		rl_on_new_line();//개행을 실행하기 위한 엔터 역할
// 		// readline 다시 실행하는 코드
// 		rl_replace_line("", 0);//buffer초기화
// 		rl_redisplay();//실행
// 		}
// 		else
// 			ft_putstr_fd("\n",1);//다시출력해서 커서가 글자의 끝에 있음.
// 	}
// 	else if(signo == SIGQUIT)
// 	{
// 		if (pid == -1) //ok.
// 		{
// 		rl_on_new_line();//입력 받은 것 종료
// 		rl_redisplay();// 입력받은 것 다시 출력
// 		ft_putstr_fd("  \b\b",1);
// 		}
// 		else
// 			ft_putstr_fd("Quit: 3\n",1);//다시출력해서 커서가 글자의 끝에 있음.
// 	}
// }

void	set_signal(void)
{
	signal (CTRL_C, signal_handler);
	signal (CTRL_SLASH, SIG_IGN);
	// if (signal (CTRL_SLASH, SIG_IGN))
	// 	g_status = g_status;
    // signal(SIGINT, handle_signal);//ctrl + c
	// signal(SIGQUIT, handle_signal);//ctrl + '\'
}
