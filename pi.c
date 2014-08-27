#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK 128


int N, N4;
char a[10240], b[10240], c[10240];
char string[100];

unsigned div_5[56][2];
unsigned div_25[276][2];
unsigned div_239[2630][2];



void lookUpTablesInit()
{
    int toSet = -1;
    int i;

    for(i = 0; i<57; i++)
    {
        if(i%5==0) toSet++;
        div_5[i][0] = toSet;
        div_5[i][1] = toSet*5;
    }

    toSet = -1;
    for(i = 0; i<277; i++)
    {
        if(i%25==0) toSet++;
        div_25[i][0] = toSet;
        div_25[i][1] = toSet*25;
    }

    toSet = -1;
    for(i = 0; i<2631; i++)
    {
        if(i%239==0) toSet++;
        div_239[i][0]= toSet;
        div_239[i][1]= toSet*239;
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
	unsigned q, r, u;

	r = 0;
	for(k=0; k<= N4; k++)
	{
		u = r * 10 + x[k];
        q = div_5[u][0];
        r = u - div_5[u][1];
        x[k] = q;                
	}
}

void DIVIDE_A25_B239_B239(char *x, char *y)
{
    int k;
    unsigned q, rx, ry1, ry2, u;

    rx = 0;
    ry1 = 0;
    ry2 = 0;
    for(k=0; k<= N4-9; k+=10)
    {
        ///////////1///////////
        u = rx * 10 + x[k];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k] = q;

        u = ry1 * 10 + y[k];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k] = q;

        ////////////2//////////////

        u = rx * 10 + x[k+1];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+1] = q;

        u = ry1 * 10 + y[k+1];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+1] = q; 

        ////////////3/////////////

        u = rx * 10 + x[k+2];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+2] = q;

        u = ry1 * 10 + y[k+2];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+2] = q;                

        /////////////4///////////////

        u = rx * 10 + x[k+3];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+3] = q;

        u = ry1 * 10 + y[k+3];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+3] = q; 

        /////////////5/////////////

        u = rx * 10 + x[k+4];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+4] = q;

        u = ry1 * 10 + y[k+4];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+4] = q; 

        ////////////6/////////////

        u = rx * 10 + x[k+5];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+5] = q;

        u = ry1 * 10 + y[k+5];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+5] = q; 

        ///////////7///////////// 

        u = rx * 10 + x[k+6];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+6] = q;

        u = ry1 * 10 + y[k+6];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+6] = q;

        ///////////8/////////////

        u = rx * 10 + x[k+7];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+7] = q;

        u = ry1 * 10 + y[k+7];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+7] = q;

        /////////9//////////////

        u = rx * 10 + x[k+8];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+8] = q;

        u = ry1 * 10 + y[k+8];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+8] = q; 

        ///////////////10////////

        u = rx * 10 + x[k+9];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k+9] = q;

        u = ry1 * 10 + y[k+9];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k+9] = q;      
    }

    for(; k<= N4; k+=10)
    {
        ///////////1///////////
        u = rx * 10 + x[k];
        q = div_25[u][0];
        rx = u - div_25[u][1];
        x[k] = q;

        u = ry1 * 10 + y[k];
        q = div_239[u][0];
        ry1 = u - div_239[u][1];

        u = ry2 * 10 + q;
        q = div_239[u][0];
        ry2 = u - div_239[u][1];
        y[k] = q;
    }


}

void DIVIDE_25(char *x)
{
	int k;
	unsigned q, r, u;

	r = 0;
	for(k=0; k<= N4; k++)
	{
		u = r * 10 + x[k];
        q = div_25[u][0];
        r = u - div_25[u][1];
        x[k] = q;                      
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
        q = div_239[u][0];
        r = u - div_239[u][1];
        x[k] = q;                        
	}
}


void DIVIDE_239_2(char *x)
{
    int k;
    unsigned q, r1,r2, u;

    
    r1 = 0;
    r2 = 0;
    for(k=0; k<= N4; k++)
    {
        u = r1 * 10 + x[k];
        q = div_239[u][0];
        r1 = u - div_239[u][1];

        u = r2 * 10 + q;
        q = div_239[u][0];
        r2 = u - div_239[u][1];
        x[k] = q;                       
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
        char tmp = y[k] - z[k];                                        
        if(tmp & MASK)           
        {                                        
            tmp += 10;                          
            z[k-1]++;                            
        }
        x[k] = tmp;                                        
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
        SUBTRACT( b, c, b );

        DIVIDE_A25_B239_B239(a,b);
        //DIVIDE_25(a);
        //DIVIDE_239_2(b);

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

