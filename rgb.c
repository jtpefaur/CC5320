#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char r;
	char g;
	char b;
} Tpixel;


#define ROWS 5000
#define COLUMNS 20000

Tpixel buffer[ROWS][COLUMNS];

void rgb_verd()
{
	unsigned int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLUMNS-2;j+=2)
		{
			*((long *)&buffer[i][j]) = 0x0000000100000100;
		}

		buffer[i][j].r=0;
		buffer[i][j].g=1;
		buffer[i][j].b=0;

		buffer[i][j+1].r=0;
		buffer[i][j+1].g=1;
		buffer[i][j+1].b=0;
	}
}

int main(int argc,char* argv[])
{
	rgb_verd();
	write(1,buffer,sizeof(buffer));
	return(0);
}
