#include "main.h"


void	test_push_buffer(void)
{
	char test[100] = "hello";
	t_buffer buffer;

	printf("++ pushing to buffer\n");
	push_to_buffer(&buffer, test, 3);
	printf("buffer contents: %s\n", buffer.data);
	
	printf("++ pushing to buffer\n");
	push_to_buffer(&buffer, test, 5);
	printf("buffer contents: %s\n", buffer.data);
}

void	test_resize_buffer(void)
{
	int size = 10;
	t_buffer buffer;
	buffer.size = 0;
	resize_buffer(&buffer, size);
	memset(buffer.data, 'A', size);

	printf("Buffer size: %d\n", buffer.size);
	printf("Buffer content: %s\n", buffer.data);
	
	printf("+++ Buffer resizing\n");
	resize_buffer(&buffer, 10);
	//memset(buffer.data, 'A', 21);

	printf("Buffer size: %d\n", buffer.size);
	printf("Buffer content: %s\n", buffer.data);
}
