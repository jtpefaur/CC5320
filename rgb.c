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
	for(i=0;i<(ROWS*COLUMNS)-2;i+=2)
	{
		*((long *)&buffer[i]) = 0x00000100000100;
	}

	buffer[i].r=0;
	buffer[i].g=1;
	buffer[i].b=0;


	buffer[i+1].r=0;
	buffer[i+1].g=1;
	buffer[i+1].b=0;
}


int main(int argc,char* argv[])
{
	rgb_verd();
	write(1,buffer,sizeof(buffer));
	return(0);
}
