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
	for(i=0;i<ROWS-1;i++)
	{
		for(j=0;j<COLUMNS;j+=2)
		{
			*((long *)&buffer[i][j]) = 0x0000000100000100;
		}

	}

	for(j=0;j<COLUMNS-2;j+=2)
	{
		*((long *)&buffer[ROWS-1][j]) = 0x0000000100000100;
	}

	buffer[ROWS-1][j].r=0;
	buffer[ROWS-1][j].g=1;
	buffer[ROWS-1][j].b=0;
	
	buffer[ROWS-1][j+1].r=0;
	buffer[ROWS-1][j+1].g=1;
	buffer[ROWS-1][j+1].b=0;


}


int main(int argc,char* argv[])
{
	rgb_verd();
	write(1,buffer,sizeof(buffer));
	return(0);
}
