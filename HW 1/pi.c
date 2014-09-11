#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK 128


int N, N4;
char a[10240], b[10240], c[10240];
char string[100];

unsigned div_5[56];
unsigned div_25[276];
unsigned div_239[2630];

void lookUpTablesInit()
{
    int toSet = -1;
    int i;

    for(i = 0; i<57; i++)
    {
        if(i%5==0) toSet++;
        div_5[i] = toSet;
    }

    toSet = -1;
    for(i = 0; i<277; i++)
    {
        if(i%25==0) toSet++;
        div_25[i] = toSet;
    }

    toSet = -1;
    for(i = 0; i<2631; i++)
    {
        if(i%239==0) toSet++;
        div_239[i]= toSet;
    }
}

void DIVIDE( char *x, int n )                           
{                                                
    int k;
    unsigned q, r, u;
    float nInv = 1.0/n;
		
    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = r * 10 + x[k];                       
        q = u *nInv;                               
        r = u - q * n;                           
        x[k] = q;                                
    }                                           
}

void DIVIDE_5(char *x)
{
	int k;
	unsigned q, r, u;

	r = 0;
	for(k=0; k<= N4; k++)
	{
		u = r * 10 + x[k];
        q = div_5[u];
        r = u - q*5;
        x[k] = q;                
	}
}

void SUBTRACT( char *x, char *y, char *z )                      
{
    int k;
    char tmp;
    for( k = N4; k >= 0; k-- )                   
    {  
        tmp = y[k] - z[k];                                                                                             
        z[k-1] = z[k-1] + ((tmp>>7)&1);
        tmp += 10*((tmp>>7)&1);                            
        x[k] = tmp;                                        
    }                                               
}

void BOTH_SUBTRACT( char *x, char *y, char *z )                      
{                                                
    int k;
    char tmp;

    for( k = N4; k >= 0; k-- )                   
    {  
        tmp = y[k] - x[k];
        x[k-1] = x[k-1] + ((tmp>>7)&1);
        tmp += 10*((tmp>>7)&1);                                         
        x[k] = tmp;

        tmp = y[k] - z[k];
        z[k-1] = z[k-1] + ((tmp>>7)&1);
        tmp += 10*((tmp>>7)&1);
        z[k] = tmp;                                        
    }                                            
}

void DIVIDE_X25_Y239_Y239(char *x, char *y, char *z)
{
    int k;
    unsigned q, rx, ry1, ry2, u;

    rx = 0;
    ry1 = 0;
    ry2 = 0;
    for(k=0; k<= N4; k++)
    {
        u = rx * 10 + x[k];
        q = div_25[u];
        rx = u - q*25;
        x[k] = q;

        u = ry1 * 10 + y[k];
        q = div_239[u];
        ry1 = u - q*239;

        u = ry2 * 10 + q;
        q = div_239[u];
        ry2 = u - q*239;
        y[k] = q;                     
    }
}

void DIVIDE_239(char *x)
{
	int k;
	unsigned q, r, u;

    
	r = 0;
	for(k=0; k<= N4; k++)
	{
        u = r * 10 + x[k];
        q = div_239[u];
        r = u - q*239;
        x[k] = q;                        
	}
}  

void MULTIPLY( char *x, int n )                        
{                                            
    int k;
    unsigned q, r;
    r = 0;                                   
    for( k = N4; k >= 0; k-- )               
    {                                        
        q = n * x[k] + r;                    
        r = q / 10;                          
        x[k] = q - r * 10;                   
    }                                        
}

void SET( char *x, int n )                              
{                                                
    memset( x, 0, N4 + 1 );                      
    x[0] = n;                                    
}

void calculate( void );
void progress( void );
void epilog( void );


int main( int argc, char *argv[] )
{
    N = 10000;

/*    if( argc > 1 )
        sscanf( argv[1], "%d", &N );

    while( N < 0 || N > 10000 )
    {
        printf( "Enter number of decimal places => " );
        scanf( "%s", string );
        sscanf( string, "%d", &N );
    }
*/

    setbuf(stdout, NULL);

    lookUpTablesInit();
    calculate();

    epilog();

    return 0;
}

void calculate( void )
{
    int j;

    N4 = N + 4;

    SET( a, 0 );
    SET( b, 0 );

    for( j = 2 * N4 + 1; j >= 3; j -= 2 )
    {
        SET( c, 1 );
        DIVIDE( c, j );

        BOTH_SUBTRACT( a, c, b );
        DIVIDE_X25_Y239_Y239(a,b,c);

        progress();
    }

    SET( c, 1 );

    SUBTRACT( a, c, a );
    DIVIDE_5(a);

    SUBTRACT( b, c, b );
    DIVIDE_239(b);

    MULTIPLY( a, 4 );
    SUBTRACT( a, a, b );
    MULTIPLY( a, 4 );

    progress();
}

/*

 N = 10000                      
 A = 0                          
 B = 0                          
 J = 2 * (N + 4) + 1            
 FOR J = J TO 3 STEP -2         
     A = (1 / J - A) / 5 ^ 2    
     B = (1 / J - B) / 239 ^ 2  
 NEXT J                         
 A = (1 - A) / 5                
 B = (1 - B) / 239              
 PI = (A * 4 - B) * 4           

*/

void progress( void )
{
    printf(".");
}

void epilog( void )
{
    int j;

    {
        fprintf( stdout, " \n3.");
        for( j = 1; j <= N; j++ )
        {
            fprintf( stdout, "%d", a[j]);
            if( j % 5  == 0 )
                if( j % 50 == 0 )
                    if( j % 250  == 0 )
                        fprintf( stdout, "    <%d>\n\n   ", j );
                    else
                        fprintf( stdout, "\n   " );
                else
                    fprintf( stdout, " " );
        }
    }
}

