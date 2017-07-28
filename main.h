#ifndef	MAIN_H
#define	MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFF_SIZE 1000000

#define	ft_strchr	strchr
#define ft_strncpy	strncpy
#define	ft_strncat	strncat
#define	ft_strcpy	strcpy
#define	ft_strlen	strlen
#define	ft_bzero	bzero

#define C_RED		"\x1b[31m"
#define C_RESET		"\x1b[0m"

typedef	struct	s_buffer
{
	char	*data;
	int		size;
}				t_buffer;


void	flush_buffer(t_buffer *buffer);
int		get_next_line(const int fd, char **line);
void	push_to_buffer(t_buffer *buffer, char *new_buffer, int buff_size);
void	resize_buffer(t_buffer *buffer, int size);
#endif
