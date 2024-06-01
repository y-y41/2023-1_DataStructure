#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int row = atoi(argv[1]);
	char **arr = (char**) malloc(row * sizeof(char *));

	for (int i=0; i<row; i++) {
		arr[i] = (char*) malloc(sizeof(char) * 30);
	}

	printf("enter %d names:\n", row);
	for (int i=0; i<row; i++) {
		scanf("%s", arr[i]);
	}
	
	printf("the names you entered:\n");
	for (int i=0; i<row; i++) {
		printf("%s\n", arr[i]);
	}

	for (int i=0; i<row; i++) {
		free(arr[i]);
	}
	free(arr);

	return 0;
}
