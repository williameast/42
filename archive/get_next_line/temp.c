
#include <stdio.h>


size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j] && j < size)
		j++;
	while (src[k] && ((j + k + 1) < size))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != size)
		dest[j + k] = '\0';
	return (j + k);
}

int main(void) {

	char line[64];

	line[0] = '\0';
	ft_strlcat(line, "my name is william", 10);
	ft_strlcat(line, "william", 10);
	printf("%s\n", line);


    return 0;
}
