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


int	get_next_line(const int fd, char **line)
{
	static int count;
	static char buffer[BUFF_SIZE + 1];
	int ret;
	int i;
	int line_count;
	int line_len;

	count++;
	i = 0;
	line_len = 0;
	line_count = 0;
	printf(" ================= GET_NEXT_LINE() ========================\n");
	if (count == 1)
		ret = read(fd, buffer, BUFF_SIZE);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{	
			line_count++;
			printf("Line count is %d\n", line_count);
			if (line_count == count)
			{
				*line = (char*)malloc(line_len * sizeof(char));
				strncpy(*line, &buffer[i - line_len], line_len);
				printf("Test: i: %d\n", i);
				printf("String copied: %s\n", *line);
				return (0);	
			}
			line_len = 0;
		}
		i++;
		line_len++;
	}
	//printf("Read result: %d\n", ret);
	//printf("Buffer contents: %s\n", buffer);	
}


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int	main(void)
{
	int fd;
	int ret;
	char buffer[BUFF_SIZE + 1];
	char *line;

	fd = open("test.txt", O_RDONLY | O_CREAT);
	if (fd)
	{
		//ret = read(fd, buffer, BUFF_SIZE);
		//printf("%s\n", buffer);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
		get_next_line(fd, &line);
	
	}
	else
	{
		// Error
		printf("error opening file \n");
	}

}
