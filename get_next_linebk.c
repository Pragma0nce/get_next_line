/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:00:04 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/25 15:59:35 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 20
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
    buffer->end = 0;
	buffer->start = 0;
}

void    resize_buffer(t_buffer *buffer)
{
    //printf(".....   Resizing buffer\n");
    // Create temporary array holding the current buffer size
    char *temp;
   	int temp_size;

    temp = (char*)malloc(sizeof(char) * (buffer->size + 2));
    buffer->stream[buffer->size] = '\0';
	//printf("----- buffer: %s\n", buffer->stream);
	strcpy(temp, buffer->stream);
	// Free the memory being used by buffer
    //printf("Attempting to free buffer with the following contents: %s\n", buffer->stream);
    
	//printf(".... got to after copy: %s \n", temp);
	free(buffer->stream);
	buffer->stream = NULL;
    //printf("got here\n");
    // Allocate double the size
    buffer->size += BUFF_SIZE;
    buffer->stream = (char*)malloc(sizeof(char) * (buffer->size + 1));
    strcpy(buffer->stream, temp);
    //printf(" ..... buffer contents:\n%s\n ++++ ++++ ++++ +++ \n", buffer->stream);
	free(temp);
	temp = NULL;
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
	should_read = 0;
    if (buffer.size == 0)
    {
		//printf("..... init buffer \n");
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

			ret = read(fd, &(buffer.stream[buffer.end]), BUFF_SIZE); 
			buffer.stream[buffer.size] = '\0';
			if (ret == 0)
            {
                return (0);
            }
        }

        //printf("========= BUFFER CONTENTS ========== \n%s\n================================\n", buffer.stream);
        // Iterate over the buffer
        i = buffer.start;
        while (buffer.stream[i])
        {
            // printf("i (%d) (%c)\n", i, buffer.stream[i]);
            if (buffer.stream[i] == '\n')
            {	
				//printf(".....   buffer.start: %c, %d\n", buffer.stream[buffer.start], buffer.start);	
                //printf(".....   buffer.end: %c, %d\n", buffer.stream[buffer.end], buffer.end);

                *line = (char*)malloc(sizeof(char) * (buffer.end - buffer.start + 1));
                //strncpy(*line, &buffer.stream[buffer.start], buffer.end - buffer.start + 1);
				strcpy(*line, &buffer.stream[buffer.start]);
				*(*line + buffer.end - buffer.start) = '\0';
				buffer.start = buffer.end + 1;
                return (1);
            }
            i++;
			buffer.end = i;
        }

        // A new line character has not been found. Resize the buffer.
        //printf("buffer.start = %d\n", buffer.start);
        //printf("buffer.end = %d\n", buffer.end);
        //buffer.end = buffer.size;
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
