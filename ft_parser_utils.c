#include "fdf.h"

/* File type check */
int	ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;	

	i = 0;
	j = 0;
	while (haystack[i] != '\0' && needle[j] != '\0')
	{
		if (haystack[i] == needle[j])
			j ++;
		i ++;
	}
	if (j == ft_strlen(needle))
		return (1);
	else
		return (0);
}

/*Free array when parsing fails*/
void	free_arr(char **arr, int cols)
{
	while (cols > -1)
	{
		free(arr[cols]);
		cols --;
	}
}