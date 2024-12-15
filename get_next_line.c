/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macovach <macovach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:46:06 by macovach          #+#    #+#             */
/*   Updated: 2024/12/15 20:46:24 by macovach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *take_after_new_line(char *buffer)
{
	int i;
	int j;
	char *remainder;

	i = 0;
	while (buffer[i] && buffer[i] != '\n') i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	remainder = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!remainder)
		return (free(buffer), NULL);
	j = 0;
	i++;
	while (buffer[i]) remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

static char *take_unit_new_line(char *content)
{
	int i;
	char *line;

	i = 0;
	if (!content[i])
		return (NULL);
	while (content && content[i] && content[i] != '\n') i++;
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

static char *read_until_new_line(int fd, char **content)
{
	char *chunk;
	int bytes_read;

	if (!*content)
		*content = (char *)ft_strdup("");
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

char *get_next_line(int fd)
{
	static char *content_store;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content_store = read_until_new_line(fd, &content_store);
	if (!content_store)
		return (NULL);
	line = take_unit_new_line(content_store);
	if (!line)
	{
		free(content_store);
		content_store = NULL;
		return (NULL);
	}
	content_store = take_after_new_line(content_store);
	return (line);
}
