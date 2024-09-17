#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#endif

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

char *get_next_line(int fd);

char *ft_strchr(const char *s, int c);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlen(const char *s);
void *ft_memcpy(void *dst, const void *src, size_t n);

#endif
