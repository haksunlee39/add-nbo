#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <arpa/inet.h>

uint32_t readFileAndNBOtoHBO(char** filename)
{
	int i;
	FILE* f;
	uint8_t nb[4];
	uint32_t* p;
	uint32_t n;
	
	if (!(f = fopen(*filename, "rb"))) //open file
	{
		perror("Couldn't open file");
		exit(0);
	}
	
	for (i = 0; i < 4; i++) // read byte by byte
		if(!fread(&nb[i], 1, 1, f))
			perror("Couldn't read from file");

	p = reinterpret_cast<uint32_t*>(nb);
	n = ntohl(*p); // NBO to HBO
	
	return n;	
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Exactly two parameters are required\n");
		exit(1);
	}
	
	uint32_t a,b;
	a = readFileAndNBOtoHBO(&argv[1]);
	b = readFileAndNBOtoHBO(&argv[2]);
	
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", a, a, b, b, a+b, a+b);
	
	return 0;
}
