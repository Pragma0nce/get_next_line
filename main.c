#include "main.h"


int		get_next_line(const int fd, char **line)
{
	int		ret;
	int		i;
	static	t_buffer buffer;
	//char	temp_buffer[BUFF_SIZE + 1];
	char	*temp_buffer;
	char	*cpy_buffer;

	if (BUFF_SIZE > SSIZE_MAX || BUFF_SIZE < 1)
	{
		printf("illegal size\n");
		return (-1);
	}
	
	temp_buffer = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while (ret = read(fd, temp_buffer, BUFF_SIZE) )
	{

		temp_buffer[ret] = '\0';
		printf("read %d characters. \n", ret);
		push_to_buffer(&buffer, temp_buffer, ret);
		if (ft_strchr(temp_buffer, '\n'))
			break;
	}

	free(temp_buffer);
	// Check if the buffer contains a \n
	i = 0;
	while (buffer.data[i])
	{
		if (buffer.data[i] == '\n')
		{
			buffer.data[i] = '\0';
			*line = (char*)malloc(sizeof(char) * i);
			ft_strcpy(*line, buffer.data);
			buffer.data[i] = '\n';

			// Pushing the leftovers to the buffer
			cpy_buffer = (char*)malloc(sizeof(char) * buffer.size);
			ft_strcpy(cpy_buffer, &(buffer.data[i + 1]));
			flush_buffer(&buffer);	
			printf("pushing the leftovers.\n");
			push_to_buffer(&buffer, cpy_buffer, ft_strlen(cpy_buffer));
			free(cpy_buffer);
			printf("returning line: \"%s\"\n", *line);
			return (1);
		}
		i++;
	}	

	return (0);
}

void	flush_buffer(t_buffer *buffer)
{
	printf("flushing the buffer.\n");
	ft_bzero(buffer->data, buffer->size);
	free(buffer->data);
	buffer->size = 0;
}

void	push_to_buffer(t_buffer *buffer, char *new_buffer, int buff_size)
{
	printf("pushing ...\"%s\" to buffer. \n", new_buffer);
	// =========================//
	resize_buffer(buffer, buff_size);
	ft_strncat(buffer->data, new_buffer, buff_size);
	printf ("buffer contents are now: \"%s\"\n", buffer->data);
}



void	resize_buffer(t_buffer *buffer, int size)
{
	char *buffer_copy;

	if (buffer->size == 0)
	{
		buffer->size = size + 1;
		buffer->data = (char*)malloc(sizeof(char) * (buffer->size));
		ft_bzero(buffer->data, buffer->size);
	}
	else
	{
		buffer_copy = (char*)malloc(sizeof(char) * buffer->size);
		ft_strncpy(buffer_copy, buffer->data, buffer->size);
		free(buffer->data);
		buffer->size += size;
		buffer->data = (char*)malloc(sizeof(char) * buffer->size);
		ft_strncpy(buffer->data, buffer_copy, buffer->size);
		free(buffer_copy);
	}
}


int		main(int argc, char **argv)
{
	char *line;
	line = NULL;
	int test = 0;
	int fd = open("test.txt", O_RDONLY | O_CREAT);
	if (fd)
	{
		while (get_next_line(fd, &line) == 1)
		{
			if (line != NULL)
			{
				printf(C_RED "+++ get_next_line() +++ \n%s\n\n" C_RESET, line);
				free(line);
			}
		}
		printf("closing file.\n");
		close(fd);
	}
	else
	{
		printf ("failed to open file. \n");
	}
}
