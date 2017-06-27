/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:00:04 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/27 14:07:33 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 50
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct  s_buffer
{
    char    *stream;
    char	*head;
    char	*tail;
    int     size;
}               t_buffer;

void resize_buffer(t_buffer *buffer);

void    init_buffer(t_buffer *buffer)
{
    buffer->size = BUFF_SIZE + 1;
    buffer->stream = (char*)malloc(sizeof(char) * (buffer->size));
    buffer->head = buffer->stream;
	buffer->tail = &(buffer->stream[buffer->size - 1]); 
	*(buffer->tail) = '\0';
	*(buffer->head) = '\0';
}
void	push_to_buffer(t_buffer *buffer, char *new_buffer)
{
	char *buffer_copy;

	if (*(buffer->head) == 0)
	{
		strcpy(buffer->stream, new_buffer);
		return;
	}
	else
	{
		buffer_copy = (char*)malloc(sizeof(char) * buffer->size);
	   	strcpy(buffer_copy, buffer->stream);
		free(buffer->stream);
		buffer->size += BUFF_SIZE;
		buffer->stream = (char*)malloc(sizeof(char) * buffer->size);
		strcpy(buffer->stream, buffer_copy);
		strcat(buffer->stream, new_buffer);
		buffer->head = buffer->stream;
		buffer->tail = &(buffer->stream[buffer->size - 1]);
		free(buffer_copy);
	}
}

void	resize_buffer(t_buffer *buffer)
{
	int		i;
	char	*temp_buffer;
	i = 0;
	while (buffer->stream[i] && buffer->stream[i] != '\n')
		i++;
	temp_buffer = (char*)malloc(sizeof(char) * (buffer->size - i));
	strcpy(temp_buffer, &(buffer->stream[i+1]));
	free(buffer->stream);
	buffer->stream= (char*)malloc(sizeof(char) * (buffer->size - i));
	strcpy(buffer->stream, temp_buffer);
}

int	get_next_line(const int fd, char **line)
{
    static t_buffer buffer;
	char temp_buffer[BUFF_SIZE + 1];
	int ret;
	int i;

	i = 0;
	if (buffer.size == 0)
		init_buffer(&buffer);
	while ((ret = read(fd, &temp_buffer, BUFF_SIZE)))
	{
		temp_buffer[BUFF_SIZE] = '\0';
		push_to_buffer(&buffer, temp_buffer);
	
		while (buffer.stream[i])
		{
			if (buffer.stream[i] == '\n')
			{
				buffer.stream[i] = '\0';
				*line = (char*)malloc(sizeof(char) * buffer.size);
				strcpy(*line, buffer.stream);
				resize_buffer(&buffer);
				return (1);
			}
			i++;
		}
	}
	return (0);
}


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int	main(void)
{
    printf("###########################################################################################################\n");
	int fd;
	int ret;
	char buffer[BUFF_SIZE + 1];
	char *line;

	//test_resize();
	
	fd = open("test.txt", O_RDONLY | O_CREAT);
	if (fd)
	{
        int i = 0;
		while(get_next_line(fd, &line))
        {
            i++;
            printf("GET_NEXT_LINE OUTPUT: %s\n", line);
			free(line);
        }
		close(fd);
        //printf("Executed: %d times\n", i);
	}
	else
	{
		// Error
		printf("error opening file \n");
	}
	
}
