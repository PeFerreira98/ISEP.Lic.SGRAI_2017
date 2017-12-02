#include "stdafx.h"

#include <string.h>

#include <stdlib.h>
#include <sys/types.h>


int *read_map(char file, char ** map)
{
	return NULL;
}

char **parseBuffer(char *buffer, int lSize)
{
	int i = 0, height = 0, width = 0, y, x;

	i = 0;
	while (i < lSize) {
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n");

	i = 0;
	while (buffer[i] != '\n' || i == lSize)
	{
		width++;
		i++;
	}
	width--;
	printf("width = %d\n", width);

	i = 0;
	while (i < lSize)
	{
		if (buffer[i] == '\n')
		{
			height++;
		}
		i++;
	}
	height++;
	printf("height = %d\n\n", height);

	//char *result = (char *)malloc(height * width * sizeof(char));

	char **result = (char **)malloc(height * sizeof(char*));
	if (!result) fputs("memory alloc fails", stderr), exit(1);
	
	for (i = 0; i < height; i++)
	{
		result[i] = (char *)malloc(width * sizeof(char));
	}

	i = 0;
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{

			if ('A' <= buffer[i] && buffer[i] <= 'Z')
			{
				result[y][x] = buffer[i];
				printf("%d,%d = %c \n", y, x, buffer[i]);
			}
			else {
				x--;
			}
			i++;

		}
	}

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			printf("%c", result[y][x]);
		}
		printf("\n");
	}
	printf("\n\n");

	return result;
}

void loadfile(char *filename)
{
	//FILE *ptrFile;
	//long lSize;
	//char *buffer;
	////int i=0;
	////int height=0, width=0;
	//int y, x;

	//ptrFile = fopen(filename, "rb");
	//if (!ptrFile) perror(filename), exit(1);

	//fseek(ptrFile, 0L, SEEK_END);
	//lSize = ftell(ptrFile);
	//rewind(ptrFile);

	///* allocate memory for entire content */
	//buffer = (char*)calloc(1, lSize + 1);
	//if (!buffer) fclose(ptrFile), fputs("memory alloc fails", stderr), exit(1);

	///* copy the file into the buffer */
	//if (1 != fread(buffer, lSize, 1, ptrFile))
	//	fclose(ptrFile), free(buffer), fputs("entire read fails", stderr), exit(1);

	///* do your work here, buffer is a string contains the whole text */

	//char **result = parseBuffer(buffer, lSize);

	//fclose(ptrFile);
	//free(buffer);
}