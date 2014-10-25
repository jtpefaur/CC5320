#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <emmintrin.h>

 
void panic(char *miss)
{
        if (errno != 0) perror(miss);
        else fprintf(stderr, "%s\n", miss);
 
        exit(1);
}
 
int main(int argc, char *argv[])
{
    char buff[BUFSIZ];
    int n;
    int i;
 

    while ((n = read(0, buff, BUFSIZ)) > 0)
    {

        /*Solo funciona si el tamano del archivo es divisible por 16bytes, se deberia
        agregar para el caso en que no lo sea*/
        for(i = 0; i<n; i+= 16)
        {
            __m128i loadBuf, leftResult, rightResult, result, num;

            //Cargo los 16bytes en el registro de 128bits
            loadBuf = _mm_load_si128((__m128i *) &buff[i]);

            //Seteo un 8 para hacer shift
            num = _mm_set_epi32(0, 0, 0, 8);

            //shift a la izquierda/derecha en 8 bits
            leftResult = _mm_sll_epi16(loadBuf, num);
            rightResult = _mm_srl_epi16(loadBuf, num);

            //un and a lo shifteado, hay 8 bits que interesan, despues los 8 siguientes no, y asi..
            num = _mm_set_epi32(0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00);
            leftResult = _mm_and_si128(leftResult, num);
            num = _mm_set_epi32(0x00ff00ff, 0x00ff00ff, 0x00ff00ff, 0x00ff00ff);
            rightResult = _mm_and_si128(rightResult, num);

            //or de los dos resultados para juntarlos, teniendo asi el swap
            result = _mm_or_si128(leftResult, rightResult);

            //cargo el resultado en el buff
            _mm_store_si128((__m128i *)&buff[i], result);

        }

        if (write(1, buff, n) < 0) panic("write");
    }
 
    if (n == -1) panic("read");
 
    return 0;
}
