#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int N, N4;
char a[10240], b[10240], c[10240];
char string[100];
char checksign = 1<<7;

unsigned q_div_5[56];
unsigned q_div_25[276];
unsigned q_div_239[2630];
unsigned q_div_5_mult_5[56];
unsigned q_div_25_mult_25[276];
unsigned q_div_239_mult_239[2630];

void lookUpTablesInit()
{
    int toSet = -1;
    int i;

    for(i = 0; i<57; i++)
    {
        if(i%5==0) toSet++;
        q_div_5[i] = toSet;
        q_div_5_mult_5[i] = toSet*5;
    }

    toSet = -1;
    for(i = 0; i<277; i++)
    {
        if(i%25==0) toSet++;
        q_div_25[i] = toSet;
        q_div_25_mult_25[i] = toSet*25;
    }

    toSet = -1;
    for(i = 0; i<2631; i++)
    {
        if(i%239==0) toSet++;
        q_div_239[i] = toSet;
        q_div_239_mult_239[i] = toSet*239;
    }
}

void DIVIDE( char *x, int n )                           
{                                                
    int k;
    unsigned q, r, u;
		
    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        u = r * 10 + x[k];                       
        q = u /n;                               
        r = u - q * n;                           
        x[k] = q;                                
    }                                           
}

void DIVIDE_5(char *x)
{
	int k;
	unsigned r, u;
	float nInv = 0.2;

	r = 0;
	for(k=0; k<= N4; k++)
	{
		u = r * 10 + x[k];
        r = u - q_div_5_mult_5[u];                           
		x[k] = q_div_5[u];
	}
}

void DIVIDE_25(char *x)
{
	int k;
	unsigned r, u;
	float nInv = 0.04;

	r = 0;
	for(k=0; k<= N4; k++)
	{
		u = r * 10 + x[k];
        r = u - q_div_25_mult_25[u];                          
		x[k] = q_div_25[u];
	}
}

void DIVIDE_239(char *x)
{
	int k;
	unsigned r, u;
	float nInv = 0.0041841;

	r = 0;
	for(k=0; k<= N4; k++)
	{
		u = r * 10 + x[k];
        r = u - q_div_239_mult_239[u];                         
		x[k] = q_div_239[u];
	}
}




void LONGDIV( char *x, int n )                          
{                                                
    int k;
    unsigned q, r, u;
    long v;

    if( n < 6553 )                               
    {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k++ )               
        {                                        
            u = r * 10 + x[k];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k] = q;                            
        }                                       
    }                                            
    else                                         
    {                                            
        r = 0;
        for( k = 0; k <= N4; k++ )              
        {                                       
            if( r < 6553 )                      
            {                                   
                u = r * 10 + x[k];              
                q = u / n;                      
                r = u - q * n;                  
            }                                   
            else                                
            {                                   
                v = (long) r * 10 + x[k];       
                q = v / n;                      
                r = v - q * n;                  
            }                                   
            x[k] = q;                           
        }                                       
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


void SUBTRACT( char *x, char *y, char *z )                      
{                                                
    int k;
    for( k = N4; k >= 0; k-- )                   
    {  
        char tmp = x[k] = y[k] - z[k];                                        
        if(tmp & checksign)           
        {                                        
            x[k] += 10;                          
            z[k-1]++;                            
        }                                        
    }                                            
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
        LONGDIV( c, j );

        SUBTRACT( a, c, a );
        DIVIDE_25(a);

        SUBTRACT( b, c, b );
        DIVIDE_239(b);
        DIVIDE_239(b);

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

