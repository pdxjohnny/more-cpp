#include "strings.h"

int strings::readline(int fd, char * buffer, int buffer_size) {
	// Index in buffer array
	int i, j = 1;
    int eof = 0;
	// Current character
	char tmp = '\0';
	// Read until newline or max - 1 for NULL terminate
	for (i = 0; i < buffer_size - 1 && j; ++i) {
		// Read in a character
		j = read(fd, &tmp, 1);
        // EOF
        if (j < 1) {
            eof = 1;
            break;
        }
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
	while (tmp != '\n' && j)
	{
		j = read(fd, &tmp, 1);
        if (j < 1) {
            eof = 1;
            break;
        }
	}
	// NULL terminate
	buffer[i] = '\0';
    if (eof) {
        return 0;
    }
	// Length of string
	return i;
}
