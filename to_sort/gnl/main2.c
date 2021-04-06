#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	char *line;
	int fd;
	int res;

	fd = open("a.txt", O_RDONLY);
	while ((res = get_next_line(0, &line)) > 0)
	{
		printf("%s|return: %i\n", line, res);
		free(line);
	}
	printf("%s|return: %i\n", line, res);
	free (line);
	close(fd);
	return (0);
}