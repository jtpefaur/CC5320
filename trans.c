/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 

#include <stdio.h>
#include "cachelab.h"


int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y, currentDiag;
    


    if(M==32 && N==32)
    {

        for (i = 0; i < N; i+=8) {
            for (j = 0; j < M; j+=8) {
                for(x=i; x<i+8; x++) {
                    for(y=j; y<j+8;y++) {

                        if(y!=x)
                        {
                            B[y][x] = A[x][y];
                        }

                        else
                        {
                            tmp = A[x][y];
                            currentDiag = x;
                        }
                    }
                    if(i==j)
                    {
                        B[currentDiag][currentDiag] = tmp;
                    }
                }
            }
        } 
    }


    else if(M==64 && N==64)
    {
        for (j = 0; j < M; j+=4){
            for (i = 0; i < N; i+=4) {
                for(x=i; x<i+4; x++) {
                    for(y=j; y<j+4;y++) {
                         
                        if(y!=x)
                        {
                            B[y][x] = A[x][y];
                        }

                        else
                        {
                            tmp = A[x][y];
                            currentDiag = x;
                        }
                    }
                    if(i==j)
                    {
                        B[currentDiag][currentDiag] = tmp;
                    }
                }
            }
        }
        
    }

    else if (M == 61 && N == 67) {
        for (j = 0; j < M;j += 17) {
            for (i = 0; i < N; i += 1) {
                for (x = i; x < i + 1 ; x++){
                    for(y = j; y < j + 17; y++) {
                        if (x <= 66 && y <= 60)
                            B[y][x] = A[x][y];
                    }
                }
            }
        }
    }

    else
    {    
        for (j = 0; j < M; j++) {
            for (i = 0; i < N; i++) {
                tmp = A[i][j];
                B[j][i] = tmp;
            }
        }
    }
}
/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char transBlocking2_desc[] = "2x2 block tiling";
void transBlocking2(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y;

    for (i = 0; i < N; i+=2) {
        for (j = 0; j < M; j+=2) {
            for(x=i; x<i+2; x++) {
                for(y=j; y<j+2;y++) {
                    tmp = A[x][y];
                    B[y][x] = tmp;
                }
            }
        }
    }    
}

char transBlocking3_desc[] = "3x3 block tiling";
void transBlocking3(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y;

    for (i = 0; i < N-1; i+=3) {
        for (j = 0; j < M-1; j+=3) {
            for(x=i; x<i+3; x++) {
                for(y=j; y<j+3;y++) {
                    tmp = A[x][y];
                    B[y][x] = tmp;
                }
            }
        }
    }

    for(int i = 0; i<N; i++) {
        tmp = A[i][M-1];
        B[M-1][i] = tmp;
    }

    for(int j = 0; j<M; j++) {
        tmp = A[N-1][j];
        B[j][N-1] = tmp;
    }
}

char transBlocking4_desc[] = "4x4 block tiling";
void transBlocking4(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y;

    for (i = 0; i < N; i+=4) {
        for (j = 0; j < M; j+=4) {
            for(x=i; x<i+4; x++) {
                for(y=j; y<j+4;y++) {
                    tmp = A[x][y];
                    B[y][x] = tmp;
                }
            }
        }
    }      
}



char transBlocking8_desc[] = "8x8 block tiling";
void transBlocking8(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y;

    for (i = 0; i < N; i+=8) {
        for (j = 0; j < M; j+=8) {
            for(x=i; x<i+8; x++) {
                for(y=j; y<j+8;y++) {
                    tmp = A[x][y];
                    B[y][x] = tmp;
                }
            }
        }
    }      
}

char transBlocking16_desc[] = "16x16 block tiling";
void transBlocking16(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y;

    for (i = 0; i < N; i+=16) {
        for (j = 0; j < M; j+=16) {
            for(x=i; x<i+16; x++) {
                for(y=j; y<j+16;y++) {
                    tmp = A[x][y];
                    B[y][x] = tmp;
                }
            }
        }
    }      
}

char transBlocking16_2_desc[] = "16x8 block tiling";
void transBlocking16_2(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp, x, y;

    for (i = 0; i < N; i+=64) {
        for (j = 0; j < M; j+=1) {
            for(x=i; x<i+64; x++) {
                for(y=j; y<j+1;y++) {
                    tmp = A[x][y];
                    B[y][x] = tmp;
                }
            }
        }
    }      
}


char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    /*registerTransFunction(transBlocking16, transBlocking16_desc);

    registerTransFunction(transBlocking8, transBlocking8_desc); 

    registerTransFunction(transBlocking4, transBlocking4_desc); 

    registerTransFunction(transBlocking2, transBlocking2_desc);

    registerTransFunction(transBlocking16_2, transBlocking16_2_desc);

    registerTransFunction(transBlocking3, transBlocking3_desc);*/

    registerTransFunction(trans, trans_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

