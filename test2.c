#include "minishell.h"


int main(void)
{
	char	*temp;

	while (1)
	{
	temp = readline("prompt>>");
	add_history(temp);
	free (temp);
	}
}