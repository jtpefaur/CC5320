#include<stdio.h>
#include<stdlib.h>

typedef struct {
	char r;
	char g;
	char b;
	char extra;
} Tpixel;


#define ROWS 5000
#define COLUMNS 20000

Tpixel buffer[ROWS][COLUMNS];

void rgb_verd()
{
	unsigned int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLUMNS;j++)
		{
		
			*((unsigned int *)&buffer[i][j]) = 256;
		}
	}
}

int main(int argc,char* argv[])
{
	printf("asd");
	rgb_verd();
	write(1,buffer,sizeof(buffer));
	return(0);
}
