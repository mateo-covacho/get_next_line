#include "get_next_line.h"

static char	*extract_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	remainder = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!remainder)
		return (free(buffer), NULL);
	j = 0;
	i++;
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

static char	*extract_line(char *content)
{
	int		i;
	char	*line;

	i = 0;
	if (!content[i])
		return (NULL);
	while (content && content[i] && content[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (content && content[i] && content[i] != '\n')
	{
		line[i] = content[i];
		i++;
	}
	if (content[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*read_and_accumulate(int fd, char **content)
{
	char	*chunk;
	int		bytes_read;

	if (!*content)
		*content = (char *) ft_strdup("");
	if (!*content)
		return (NULL);
	chunk = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!chunk)
		return (free(*content), NULL);
	bytes_read = 1;
	while (!ft_strchr(*content, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(chunk), free(*content), NULL);
		chunk[bytes_read] = '\0';
		*content = ft_strjoin(*content, chunk);
		if (!*content)
			return (free(chunk), NULL);
	}
	return (free(chunk), *content);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = read_and_accumulate(fd, &content);
	if (!content)
		return (NULL);
	line = extract_line(content);
	if (!line)
	{
		free(content);
		content = NULL;
		return (NULL);
	}
	content = extract_remainder(content);
	return (line);
}

/*int main()
{
	//Simple main
	
	int	fd;
	char	*line;

	fd = open("t1", O_RDONLY);
	while ((line = get_next_line(1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("%s", line);
	close(fd);
	return (0);
}*/

/*int	main(int argc, char *argv[])
{
	char *buffer;

	// Read from file if an argument is provided on the command line
	if (argc == 2)
	{
		// Open the file for reading
		int fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}

		// Calling the function to read the file contents
		while ((buffer = get_next_line(fd)) != NULL)
		{
			// Check if memory was allocated correctly
			if (buffer == NULL)
			{
				fprintf(stderr, "Failure to allocate buffer memory\n");
				break;
			}

			// Process the line read
			printf("RECEIVED: %s\n", buffer);

			// Release memory allocated to the line
			free(buffer);
		}

		// Close file descriptor
		if (close(fd) == -1)
		{
			perror("Error closing file");
			exit(EXIT_FAILURE);
		}
	}
	// Read from stdin if no arguments are provided on the command line
	else if (argc == 1)
	{
		printf("Enter text from stdin:\n");
		while ((buffer = get_next_line(STDIN_FILENO)) != NULL)
		{
			// Check if memory was allocated correctly
			if (buffer == NULL)
			{
				fprintf(stderr, "Failure to allocate buffer memory\n");
				break;
			}

			// Process the line read
			printf("RECEIVED: %s\n", buffer);

			// Release memory allocated to the line
			free(buffer);
		}
	}
	else
	{
		fprintf(stderr, "Uso: %s [nombre_del_archivo]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return 0;
}*/
