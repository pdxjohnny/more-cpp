#include "strings.h"

int strings::readline(int fd, char * buffer, int buffer_size) {
	// Index in buffer array
	int i, j = 1;
	// Current character
	char tmp;
	// Read until newline or max - 1 for NULL terminate
	for (i = 0; i < buffer_size - 1 && j; ++i) {
		// Read in a character
		j = read(fd, &tmp, 1);
		// If we are at a newline then we are done
		if ( tmp == '\n' )
		{
			break;
		}
		// Other wise copy charaters into the buffer
		else
		{
			buffer[ i ] = tmp;
		}
	}
	// Remove the newline from stdin
	while (tmp != '\n')
	{
		j = read(fd, &tmp, 1);
	}
	// NULL terminate
	buffer[i] = '\0';
	// Length of string
	return i;
}
