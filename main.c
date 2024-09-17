#include <string.h>
#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line;

	// Test reading from a file
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}

	printf("Reading from file:\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);

	// Test reading from standard input
	printf("\nReading from standard input (type 'quit' to exit):\n");
	while ((line = get_next_line(0)) != NULL)
	{
		printf("Line read: %s", line);
		if (strcmp(line, "quit\n") == 0)
		{
			free(line);
			break;
		}
		free(line);
	}

	return 0;
}
