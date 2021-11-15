#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *str = (argv[1]);
	assert(str != NULL);
	printf("Hello world, %s", str);
    return 0;
}