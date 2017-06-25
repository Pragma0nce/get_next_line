/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:00:04 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/21 12:44:49 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 32
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct  s_buffer
{
    char    *stream;
    int     start;
    int     end;
    int     size;
}               t_buffer;

void    init_buffer(t_buffer *buffer)
{
    buffer->size = BUFF_SIZE;
    buffer->stream = (char*)malloc(sizeof(char) * (buffer->size + 1));
    //buffer->end = buffer->size - 1;
}

void    resize_buffer(t_buffer *buffer)
{
    //printf(".....   Resizing buffer\n");
    // Create temporary array holding the current buffer size
    char *temp;
    
    temp = (char*)malloc(sizeof(char) * (buffer->size + 1));
    if (temp == NULL)
        printf("----- Memory allcoation of %d chars failed\n", buffer->size);
    strcpy(temp, buffer->stream);
    // Free the memory being used by buffer
    //printf("Attempting to free buffer with the following contents: %s\n", buffer->stream);
    free(buffer->stream);
    //printf("got here\n");
    // Allocate double the size
    buffer->size += BUFF_SIZE;
    buffer->stream = (char*)malloc(sizeof(char) * (buffer->size + 1));
    strcpy(buffer->stream, temp);
    free(temp);
}

int	get_next_line(const int fd, char **line)
{
    static t_buffer buffer;
    int ret;
    int i;
    int found;
    int should_read;

    //printf("\n+++ GET_NEXT_LINE ++++++++++++++++++++++++++++++++++++++++++++++++ \n\n");
    // Init
    found = 0;
    if (buffer.size == 0)
    {
        init_buffer(&buffer);
        should_read = 1;
    }
    // While a new line has not been found
    while (!found)
    {
        // Read the stream into a buffer
        if (should_read)
        {
            should_read = 0;
            //printf(".....   Reading data into buffer object\n");
            ret = read(fd, &(buffer.stream[buffer.end]), BUFF_SIZE);
            if (ret == 0)
            {
                return (0);
            }
            //printf("............. buffer contents ...........\n%s\n..................................... \n", buffer.stream);
        }

        //printf("============= BUFFER CONTENTS ============== \n%s\n========================================\n", buffer.stream);
        // Iterate over the buffer
        i = buffer.start;
        while (buffer.stream[i])
        {
            //printf("i (%d)\n", i);
            if (buffer.stream[i] == '\n')
            {
                buffer.end = i;
                *line = (char*)malloc(sizeof(char) * (buffer.end - buffer.start + 1));
                strncpy(*line, &buffer.stream[buffer.start], buffer.end - buffer.start);
                buffer.start = buffer.end + 1;
                printf(".....   line: %s\n", *line);
                return (1);
            }
            i++;
        }

        // A new line character has not been found. Resize the buffer.
        //printf("buffer.start = %d\n", buffer.start);
        //printf("buffer.end = %d\n", buffer.end);
        //printf("i: %d\n", i);
        buffer.end = buffer.size;
        should_read = 1;
        resize_buffer(&buffer);
    }
    printf(".....   Did not return.\n");
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

	fd = open("test.txt", O_RDONLY | O_CREAT);
	if (fd)
	{
        int i = 0;
		while(get_next_line(fd, &line))
        {
            i++;
            printf("%s", line);
        }
        printf("Executed: %d times\n", i);
	}
	else
	{
		// Error
		printf("error opening file \n");
	}

}
