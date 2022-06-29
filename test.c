#include "minishell.h"

int	ftt_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	i = 0;
	while (i < n && a2[i] != '\0')
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	if (i == n || a1[i] == '\0')
		return (0);
	else
		return (a1[i]);
}

int main(void)
{
	char	*s1 = "aaa";
	char	*s2;

	s2 = readline(">");
	printf ("%d\n", ftt_strncmp(s1, s2, ft_strlen(s1)));
	printf ("%d\n", ftt_strncmp(s1, s2, ft_strlen(s2)));

}