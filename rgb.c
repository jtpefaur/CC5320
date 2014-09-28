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
	for(i=0;i<(ROWS*COLUMNS) - 6;i+=8)
	{
		*((long *)&buffer[i]) = 0x00000100000100;
		*((long *)&buffer[i+2]) = 0x00000100000100;
		*((long *)&buffer[i+4]) = 0x00000100000100;
		*((long *)&buffer[i+6]) = 0x00000100000100;
	}

	for(;i<(ROWS*COLUMNS);i++)
	{
		buffer[i].r=0;
		buffer[i].g=1;
		buffer[i].b=0;
	}
}


int main(int argc,char* argv[])
{
	rgb_verd();
	write(1,buffer,sizeof(buffer));
	return(0);
}
