#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char r;
	char g;
	char b;
} Tpixel;


#define ROWS 5000
#define COLUMNS 20000

Tpixel buffer[ROWS*COLUMNS];

void rgb_verd()
{
	unsigned int i;
	char* castedBuffer = (char *)buffer;
	for(i=0;i<(ROWS*COLUMNS*3)-23;i+=24)
	{
		*((long *)&castedBuffer[i]) = 0x0100000100000100;
		*((long *)&castedBuffer[i+8]) = 0x0000010000010000;
		*((long *)&castedBuffer[i+16]) = 0x0001000001000001;
	}

	for(;i<(ROWS*COLUMNS*3);i+=3)
	{
		castedBuffer[i] = 0;
		castedBuffer[i+1] = 1;
		castedBuffer[i+2] = 0;
	}
}


int main(int argc,char* argv[])
{
	rgb_verd();
	write(1,buffer,sizeof(buffer));
	return(0);
}
