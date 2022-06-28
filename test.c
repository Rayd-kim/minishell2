#include "minishell.h"

// void	sig_handler(int sig)
// {
// 	printf("\npress button\n");
// }


void	sig_control_c(int sig)
{
	printf("\b\b  \b\b\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{

	// signal(SIGINT, sig_handler);
	// signal(SIGTERM, sig_handler);
	// signal(SIGQUIT, sig_handler);
	char	*temp;
	int		t = 0;

	signal(SIGINT, sig_control_c);
	while (1)
	{
		while (!t)
		{
			temp = readline ("prompt>>");
			printf ("%s\n", temp);
			free(temp);
		}
	}
	return (0);
}


// void (*old_fun)( int);

// void sigint_handler( int signo)
// {
//    printf( "Ctrl-C 키를 눌루셨죠!!\n");
//    printf( "또 누르시면 종료됩니다.\n");
// //    signal( SIGINT, old_fun);   // 또는 signal( SIGINT, SIG_DFL);
// }

// int main( void)
// {
//    signal( SIGINT, sigint_handler);
//    while(1 ){
//       printf( "badayak.com\n");
//       sleep( 1);
//    }
// }