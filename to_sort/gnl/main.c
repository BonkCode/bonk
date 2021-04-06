#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	char *line;
	int fd;
	int fd2;
	int fd3;

	fd = open("a.txt", O_RDONLY);
	fd2 = open("b.txt", O_RDONLY);
	fd3 = open("c.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	free(line);
	get_next_line(fd2, &line);
	printf("%s\n", line);
	free(line);
	get_next_line(fd3, &line);
	printf("%s\n", line);
	free(line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	free(line);
	get_next_line(fd2, &line);
	printf("%s\n", line);
	free(line);
	get_next_line(fd3, &line);
	printf("%s\n", line);
	free(line);
	printf ("fd: %i fd2: %i fd3: %i\n", fd, fd2, fd3);
	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}