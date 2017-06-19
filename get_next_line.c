/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:00:04 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/19 11:52:34 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 32
#include <unistd.h>

int	get_next_line(const int fd, char **line)
{
	int ret;
	int i;
	int line_count;
	char buffer[BUFF_SIZE + 1];
	if (fd == -1)
		return (-1);
	
	// Get the full size of the buffer
	while (ret = read(fd, buf, BUF_SIZE))
	{
		buffer[ret] = '\0';
		
	}

	// Actually proccesing the text
	i = 0;
	while (ret = read(fd, buf, BUF_SIZE))
	{
		buffer[ret] = '\0';
		while (buffer[i] != '\n') 
		{

		}
		// Print the current buffer
	}	
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

	fd = open("test.txt", O_RDONLY | O_CREAT);
	if (fd)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		printf("%s\n", buffer);
	}
	else
	{
		// Error
		printf("error opening file \n");
	}

}
